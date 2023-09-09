/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <phk@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */
#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

#define MSG(a) c_nix_fdwrite(2, (a), sizeof((a)))

#define M1 (C_NIX_PROTREAD|C_NIX_PROTWRITE)
#define M2 (C_NIX_MAPANON|C_NIX_MAPPRIV)
#define MMAP(a) c_nix_mmap(0, (a), M1, M2, -1, 0)

#define MNOTMINE ((struct pginfo *)0)
#define MFREE    ((struct pginfo *)1)
#define MFIRST   ((struct pginfo *)2)
#define MFOLLOW  ((struct pginfo *)3)
#define MMAGIC   ((struct pginfo *)4)

#define MBITS ((int)(8*sizeof(uint)))

#define mminsize 16U
#define mmaxsize ((mpagesize)>>1)

#define pageround(a) (((a)+mpagemask)&(~mpagemask))
#define ptr2idx(a)   (((usize)(uintptr)(a)>>mpageshift)-morigo)

/* !!! */
#define brk(a) (c_sys_brk((a)))
#define sbrk(a) (c_sys_sbrk((a)))

struct pginfo {
	struct pginfo *next;
	void *page;
	ushort size;
	ushort shift;
	ushort free;
	ushort total;
	uint bits[1];
};

struct pgfree {
	struct pgfree *next;
	struct pgfree *prev;
	void *page;
	void *end;
	usize size;
};

static union {
	uchar uc[16];
	long double ld;
} const zeroblock;
char *alloc0 = (char *)(uintptr)&zeroblock;

static struct pginfo **pagedir;
static struct pgfree freelist;
static struct pgfree *px; /* freelist cache */
static usize lastidx; /* last relevant index in the page dir */
static usize mcache = 16; /* freepages to cache */
static usize minfo; /* slots in the page dir */
static usize morigo; /* offset from pagenumber to index into the page dir */
static usize mpagemask;
static usize mpageshift;
static usize mpagesize;
static int mstt; /* malloc started */
static void *mbrk; /* last break */

static void *imalloc(usize);
static void ifree(void *);

static void
freepages(void *p, usize idx, struct pginfo *info)
{
	struct pgfree *pf, *pt;
	usize l, i;
	void *t;

	 /* pointer to wrong page */
	if (!(info == MFIRST))
		return;

	/* modified page pointer */
	if ((uintptr)p & mpagemask)
		return;

	pagedir[idx] = MFREE;
	for (i = 1; pagedir[idx + i] == MFOLLOW; ++i)
		pagedir[idx + i] = MFREE;
	l = i << mpageshift;

	if (!px)
		px = imalloc(sizeof(*px));
	px->page = p;
	px->end = t = (void *)((uchar *)p + l);
	px->size = l;
	pt = nil;
	if (!freelist.next) {
		px->next = freelist.next;
		px->prev = &freelist;
		freelist.next = px;
		pf = px;
		px = nil;
	} else {
		for (pf = freelist.next; pf->end < p && pf->next;
		    pf = pf->next) ;
		if (pf->page > t) {
			px->next = pf;
			px->prev = pf->prev;
			pf->prev = px->prev->next = px;
			pf = px;
			px = nil;
		} else if (pf->end == p) {
			pf->end = (uchar *)pf->end + l;
			pf->size += l;
			if (pf->next && pf->end == pf->next->page) {
				pt = pf->next;
				pf->end = pt->end;
				pf->size += pt->size;
				if ((pf->next = pt->next))
					pf->next->prev = pf;
			}
		} else if (pf->page == t) {
			pf->size += l;
			pf->page = p;
		} else if (!pf->next) {
			px->next = nil;
			px->prev = pf;
			pf->next = px;
			pf = px;
			px = nil;
		} else {
			MSG("freelist is destroyed\n");
			c_nix_abort();
		}
	}
	if (!pf->next &&
	    pf->size > mcache &&
	    pf->end == mbrk &&
	    mbrk == sbrk(0)) {
		pf->end = (uchar *)pf->page + mcache;
		pf->size = mcache;
		brk(pf->end);
		mbrk = pf->end;
		idx = ptr2idx(pf->end);
		for (i = idx; i <= lastidx; ++i)
			pagedir[i] = MNOTMINE;
		lastidx = idx - 1;
	}
	if (pt)
		ifree(pt);
}

static void
freebytes(void *p, usize idx, struct pginfo *info)
{
	struct pginfo **mp;
	usize i;

	/* modified chunk */
	if ((usize)(uintptr)p & (info->size - 1))
		return;

	i = ((usize)(uintptr)p & mpagemask) >> info->shift;
	/* chunk is already free */
	if (info->bits[i / MBITS] & (1UL << (i % MBITS)))
		return;

	info->bits[i / MBITS] |= (1UL << (i % MBITS));
	++info->free;
	mp = pagedir + info->shift;
	if (info->free == 1) {
		while (*mp && (*mp)->next && (*mp)->next->page < info->page)
			mp = &(*mp)->next;
		info->next = *mp;
		*mp = info;
		return;
	} else if (info->free != info->total) {
		return;
	}
	for (; *mp != info; mp = &(*mp)->next) ;
	*mp = info->next;
	pagedir[idx] = MFIRST;

	if (info->page != info)
		ifree(info);
	ifree(info->page);
}

static void
ifree(void *p)
{
	struct pginfo *i;
	usize idx;

	if (!p)
		return;

	idx = ptr2idx(p);
	/* too low or too high */
	if (idx < mpageshift || idx > lastidx)
		return;

	if ((i = pagedir[idx]) > MMAGIC)
		freebytes(p, idx, i);
	else
		freepages(p, idx, i);
}

static int
extendpgdir(usize idx)
{
	struct pginfo **p, **o;
	usize nl, ol;

	if ((((~(1UL << ((sizeof(usize) * 8) - 1)) / sizeof(*pagedir)) + 1)
	    + (mpagesize / sizeof(*pagedir))) < idx) {
		errno = C_ERR_ENOMEM;
		return 0;
	}

	nl = pageround(idx * sizeof(*pagedir)) + mpagesize;
	if ((p = MMAP(nl)) == C_NIX_MAPFAIL)
		return 0;

	ol = minfo * sizeof(*pagedir);
	c_mem_cpy(p, pagedir, ol);

	minfo = nl / sizeof(*pagedir);
	o = pagedir;
	pagedir = p;
	c_nix_munmap(o, ol);
	return 1;
}

static void *
mappages(usize pages)
{
	intptr bytes;
	void *r, *rr, *t;

	bytes = pages << mpageshift;
	if (bytes < 0 || bytes < (intptr)pages) {
		errno = C_ERR_ENOMEM;
		return nil;
	}

	if ((r = sbrk(bytes)) == (void *)-1)
		return nil;
	if ((rr = (void *)pageround((usize)(uintptr)r)) > r) {
		if (sbrk((uchar *)rr - (uchar *)r) == (void *)-1 && brk(r)) {
			MSG("brk(2) failed [internal error]\n");
			c_nix_abort();
		}
	}

	t = (uchar *)rr + bytes;
	lastidx = ptr2idx(t) - 1;
	mbrk = t;
	if ((lastidx + 1) >= minfo && !extendpgdir(lastidx)) {
		lastidx = ptr2idx((mbrk = r)) - 1;
		if (brk(mbrk)) {
			MSG("brk(2) failed [internal error]\n");
			c_nix_abort();
		}
		return nil;
	}
	return rr;
}

static void *
allocpages(usize n)
{
	struct pgfree *pf;
	usize i, idx;
	void *p, *df;

	if ((idx = pageround(n)) < n) {
		errno = C_ERR_ENOMEM;
		return nil;
	}

	n = idx;
	df = p = nil;
	for (pf = freelist.next; pf; pf = pf->next) {
		if (pf->size < n)
			continue;
		if (pf->size == n) {
			p = pf->page;
			if (pf->next)
				pf->next->prev = pf->prev;
			pf->prev->next = pf->next;
			df = pf;
			break;
		}
		p = pf->page;
		pf->page = (uchar *)pf->page + n;
		pf->size -= n;
		break;
	}

	n >>= mpageshift;
	if (!p)
		p = mappages(n);
	if (p) {
		idx = ptr2idx(p);
		pagedir[idx] = MFIRST;
		for (i = 1; i < n; ++i)
			pagedir[idx + i] = MFOLLOW;
	}
	if (df) {
		if (!px)
			px = df;
		else
			ifree(df);
	}
	return p;
}

static int
allocchunks(int bits)
{
	struct pginfo *bp;
	long l;
	int i, k;
	void *pp;

	if (!(pp = allocpages(mpagesize)))
		return 0;

	l = c_std_offsetof(struct pginfo, bits[0]);
	l += sizeof(bp->bits[0]) * (((mpagesize >> bits) + MBITS - 1) / MBITS);
	if ((1 << bits) <= (l << 1)) {
		bp = pp;
	} else {
		if (!(bp = imalloc(l))) {
			ifree(pp);
			return 0;
		}
	}

	k = bp->total = bp->free = mpagesize >> bits;
	for (i = 0; k - i >= MBITS; i += MBITS)
		bp->bits[i / MBITS] = ~0U;

	for (; i < k; ++i)
		bp->bits[i / MBITS] |= 1 << (i % MBITS);

	bp->page = pp;
	if (bp == bp->page) {
		for (i = 0; l > 0; ++i) {
			bp->bits[i / MBITS] &= ~(1 << (i % MBITS));
			--bp->free;
			--bp->total;
			l -= 1 << bits;
		}
	}
	bp->size = (1 << bits);
	bp->shift = bits;
	pagedir[ptr2idx(pp)] = bp;
	bp->next = pagedir[bits];
	pagedir[bits] = bp;
	return 1;
}

static void *
allocbytes(usize n)
{
	struct pginfo *bp;
	usize i, k;
	int j;
	uint *lp;
	uint u;

	if (n < mminsize)
		n = mminsize;

	for (i = n - (j = 1); i >>= 1; ++j) ;

	if (!pagedir[j] && !allocchunks(j))
		return nil;

	bp = pagedir[j];
	for (lp = bp->bits; !*lp; ++lp) ;

	u = 1;
	for (k = 0; !(*lp & u); ++k)
		u += u;

	if (!--bp->free) {
		pagedir[j] = bp->next;
		bp->next = nil;
	}

	*lp ^= u;
	k += (lp - bp->bits) * MBITS;
	k <<= bp->shift;
	return (uchar *)bp->page + k;
}

static void *
imalloc(usize n)
{
	if ((n + mpagesize) < n || (n + mpagesize) >= (uintptr)pagedir)
		return nil;
	if (n <= mmaxsize)
		return allocbytes(n);
	return allocpages(n);
}

static void *
irealloc(void *p, usize n)
{
	struct pginfo **mp;
	usize i, o, idx;
	void *np;

	idx = ptr2idx(p);
	/* too low or too high */
	if (idx < mpageshift || idx > lastidx)
		return nil;

	if (*(mp = &pagedir[idx]) == MFIRST) {
		/* modified (page-) pointer */
		if ((usize)(uintptr)p & mpagemask)
			return nil;
		for (o = mpagesize; *++mp == MFOLLOW; o += mpagesize) ;
		if (n <= o && n > (o - mpagesize))
			return p;
	} else if (*mp >= MMAGIC) {
		/* modified (chunk-) pointer */
		if ((usize)(uintptr)p & ((*mp)->size - 1))
			return nil;

		i = ((usize)(uintptr)p & mpagemask) >> (*mp)->shift;
		/* chunk is already free */
		if ((*mp)->bits[i / MBITS] & (1UL << (i % MBITS)))
			return nil;

		o = (*mp)->size;
		if (n <= o && (n > (o >> 1) || o == mminsize))
			return p;
	} else {
		/* pointer to wrong place */
		return nil;
	}
	if ((np = imalloc(n))) {
		if (n && o) c_mem_cpy(np, p, C_STD_MIN(n, o));
		ifree(p);
	}
	return np;
}

static void
minit(void)
{
	mpagesize = C_LIM_PAGESIZE; /* !!! */
	for (mpageshift = 0; (1UL << mpageshift) != mpagesize; ++mpageshift) ;
	mpagemask = mpagesize - 1;
	if ((pagedir = MMAP(mpagesize)) == C_NIX_MAPFAIL) {
		MSG("mmap(2) failed, check limits\n");
		c_nix_abort();
	}
	minfo = mpagesize / sizeof(*pagedir);
	mcache <<= mpageshift;
	morigo = pageround((usize)(uintptr)sbrk(0)) >> mpageshift;
	morigo -= mpageshift;
	px = imalloc(sizeof(*px));
}

void *
pubrealloc(void *p, usize m, usize n)
{
	void *r;

	if (C_STD_OVERFLOWM(usize, m, n)) {
		errno = C_ERR_EOVERFLOW;
		return nil;
	}

	r = nil;
	if (!mstt) {
		if (p)
			goto invalid;
		minit();
		++mstt;
	}

	if (p == alloc0)
		goto invalid;

	if (!m) {
		if (p) {
			ifree(p);
			return nil;
		}
		r = alloc0;
	} else {
		m *= n;
		if (!(r = p ? irealloc(p, m) : imalloc(m)))
			errno = C_ERR_ENOMEM;
	}

	return r;
invalid:
	errno = C_ERR_EINVAL;
	return r;
}
