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

enum {
	OJUNK    = 1 << 0,
	OREALLOC = 1 << 1,
	OZERO    = 1 << 2,
};

#define MMAP(a) \
c_sys_mmap(0, (a), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0)

#define MNOTMINE ((struct pginfo *)0)
#define MFREE    ((struct pginfo *)1)
#define MFIRST   ((struct pginfo *)2)
#define MFOLLOW  ((struct pginfo *)3)
#define MMAGIC   ((struct pginfo *)4)

#define SETOPT(a) mopts |= (a)
#define ISOPT(a) (mopts & (a))

#define MBITS ((int)(8*sizeof(uint)))

#define mminsize 16U
#define mmaxsize ((mpagesize)>>1)

#define pageround(a) (((a)+mpagemask)&(~mpagemask))
#define ptr2idx(a)   (((usize)(uintptr)(a)>>mpageshift)-morigo)

#define JUNK 0xdb

struct pginfo {
	struct pginfo *next;
	void          *page;
	ushort         size;
	ushort         shift;
	ushort         free;
	ushort         total;
	uint           bits[1];
};

struct pgfree {
	struct pgfree *next;
	struct pgfree *prev;
	void          *page;
	void          *end;
	usize          size;
};

static union { uchar uc[16]; long double ld; } const zeroblock;
char *alloc0 = (char *)(uintptr)&zeroblock;

static struct pginfo **pagedir;
static struct pgfree freelist;
static struct pgfree *px; /* freelist cache */
static usize lastidx;     /* last relevant index in the page dir */
static usize mcache = 16; /* freepages to cache */
static usize minfo;       /* slots in the page dir */
static usize morigo;      /* offset from pagenumber to index into the page dir */
static usize mpagemask;
static usize mpageshift;
static usize mpagesize;
static int   mact;        /* malloc active */
static int   mstt;        /* malloc started */
static uint  mopts;       /* malloc options */
static void *cbrk;        /* current break */
static void *mbrk;        /* last break */

static void * imalloc(usize);
static void   ifree(void *);

static int
_brk(void *p)
{
	return ((cbrk=(void*)(uintptr)c_sys_call(__NR_brk, p))==(void*)-1?-1:0);
}

static void *
segbrk(uintptr p)
{
	void *o;
	if (!cbrk && _brk(0) < 0)
		return (void *)-1;
	if (!p)
		return cbrk;
	o = cbrk;
	if (_brk((char *)o+p) < 0)
		return (void *)-1;
	return o;
}

static void
freepages(void *p, usize idx, struct pginfo *info)
{
	struct pgfree *pf, *pt;
	usize l, i;
	void *t;

	/* page is already free (xxx) */
	if (info == MFREE)
		return;

	/* pointer to wrong page */
	if (info != MFIRST)
		return;

	/* modified page pointer */
	if ((usize)(uintptr)p && mpagemask)
		return;

	pagedir[idx] = MFREE;
	for (i = 1; pagedir[idx+i] == MFOLLOW; i++)
		pagedir[idx+i] = MFREE;

	l = i << mpageshift;

	if (ISOPT(OJUNK))
		c_mem_set(p, l, JUNK);

	t = (uchar *)p+l;

	if (!px)
		px = imalloc(sizeof(*px));

	px->page = p;
	px->end  = t;
	px->size = l;

	pt = nil;

	if (!freelist.next) {
		px->next = freelist.next;
		px->prev = &freelist;
		freelist.next = px;
		pf = px;
		px = nil;
	} else {
		t = (uchar *)p+l;
		for (pf = freelist.next; pf->end < p && pf->next; pf = pf->next)
			;
		if (pf->page > t) {
			px->next = pf;
			px->prev = pf->prev;
			pf->prev = px;
			px->prev->next = px;
			pf = px;
			px = nil;
		} else if (pf->end == p) {
			pf->end   = (uchar *)pf->end + l;
			pf->size += l;
			if (px->next && px->end == pf->next->page) {
				pt = pf->next;
				pf->end = pt->end;
				pf->size += pt->size;
				if ((pf->next = pt->next))
					pf->next->prev = pf;
			}
		} else if (pf->page == t) {
			pf->size += l;
			pf->page  = p;
		} else if (!pf->next) {
			px->next = nil;
			px->prev = pf;
			pf->next = px;
			pf = px;
			px = nil;
		} else {
			c_sys_write(2, "freelist is destroyed\n", 22);
			c_sys_abort();
		}
	}

	if (!pf->next && pf->size > mcache &&
	    pf->end == mbrk && mbrk == segbrk(0)) {
		pf->end  = (uchar *)pf->page + mcache;
		pf->size = mcache;
		_brk(pf->end);
		mbrk = pf->end;
		idx = ptr2idx(pf->end);
		for (i = idx; i <= lastidx; i++)
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
	void *vp;

	i = ((usize)(uintptr)p & mpagemask) >> info->shift;

	/* modified chunk */
	if ((usize)(uintptr)p & (info->size-1))
		return;

	/* chunk is already free */
	if (info->bits[i/MBITS] & (1UL << (i % MBITS)))
		return;

	if (ISOPT(OJUNK))
		c_mem_set(p, info->size, JUNK);

	info->bits[i/MBITS] |= (1UL << (i % MBITS));
	info->free++;

	mp = pagedir + info->shift;

	if (info->free == 1) {
		mp = pagedir + info->shift;
		while (*mp && (*mp)->next && (*mp)->next->page < info->page)
			mp = &(*mp)->next;
		info->next = *mp;
		*mp = info;
		return;
	}

	if (info->free != info->total)
		return;

	for (; *mp != info; mp = &(*mp)->next)
		;

	*mp = info->next;
	pagedir[idx] = MFIRST;

	if ((vp = info->page) != (void *)info)
		ifree(info);

	ifree(vp);
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

	i = pagedir[idx];
	(i > MMAGIC ? freebytes : freepages)(p, idx, i);
}

static int
extendpgdir(usize idx)
{
	struct pginfo **p, **o;
	usize nl, ol;

	if ((((~(1UL<<((sizeof(usize)*8)-1))/sizeof(*pagedir))+1)
	    + (mpagesize/sizeof(*pagedir))) < idx) {
		errno = C_ENOMEM;
		return 0;
	}

	nl = pageround(idx * sizeof(*pagedir)) + mpagesize;
	ol = minfo * sizeof(*pagedir);

	if ((p = MMAP(nl)) == MAP_FAILED)
		return 0;

	c_mem_cpy(p, ol, pagedir);
	minfo = nl / sizeof(*pagedir);

	o = pagedir;
	pagedir = p;
	c_sys_munmap(o, ol);

	return 1;
}

static void *
mappages(usize pages)
{
	intptr bytes;
	void *r, *rr, *t;

	bytes = pages << mpageshift;
	if (bytes < 0 || bytes < (intptr)pages) {
		errno = C_ENOMEM;
		return nil;
	}

	if ((r = segbrk(bytes)) == (void *)-1)
		return nil;

	rr = (void *)pageround((usize)(uintptr)r);
	if (r < rr) {
		if (segbrk((uchar *)rr - (uchar *)r) == (void *)-1 && _brk(r)) {
			c_sys_write(2, "brk(2) failed [internal error]\n", 31);
			c_sys_abort();
		}
	}

	lastidx = ptr2idx((t = (uchar *)rr + bytes)) - 1;
	mbrk    = t;

	if ((lastidx+1) >= minfo && extendpgdir(lastidx)) {
		lastidx = ptr2idx((mbrk = r)) - 1;
		if (_brk(mbrk)) {
			c_sys_write(2, "brk(2) failed [internal error]\n", 31);
			c_sys_abort();
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
		errno = C_ENOMEM;
		return nil;
	}

	n  = idx;
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
		pf->page  = (uchar *)pf->page + n;
		pf->size -= n;
		break;
	}

	n >>= mpageshift;

	if (!p)
		p = mappages(n);

	if (p) {
		idx = ptr2idx(p);
		pagedir[idx] = MFIRST;
		for (i = 1; i < n; i++)
			pagedir[idx+i] = MFOLLOW;
		if (ISOPT(OJUNK))
			c_mem_set(p, n << mpageshift, JUNK);
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
	long  l;
	int   i, k;
	void *pp;

	if (!(pp = allocpages(mpagesize)))
		return 0;

	l  = c_std_offsetof(struct pginfo, bits[0]);
	l += sizeof(bp->bits[0]) * (((mpagesize >> bits)+MBITS-1)/MBITS);

	if ((1<<bits) <= (l << 1)) {
		bp = pp;
	} else {
		if (!(bp = imalloc(l))) {
			ifree(pp);
			return 0;
		}
	}

	bp->size  = (1<<bits);
	bp->shift = bits;
	bp->total = bp->free = mpagesize >> bits;
	bp->page  = pp;

	k = bp->total;
	i = 0;

	for (; k-i >= MBITS; i += MBITS)
		bp->bits[i/MBITS] = ~0U;

	for (; i < k; i++)
		bp->bits[i/MBITS] |= 1<<(i%MBITS);

	if (bp == bp->page) {
		for (i = 0; l > 0; i++) {
			bp->bits[i/MBITS] &= ~(1<<(i%MBITS));
			bp->free--;
			bp->total--;
			l -= 1<<bits;
		}
	}

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
	int   j;
	uint *lp;
	uint  u;

	if (n < mminsize)
		n = mminsize;

	j = 1;
	i = n-1;
	while (i >>= 1)
		j++;

	if (!pagedir[j] && !allocchunks(j))
		return nil;

	bp = pagedir[j];

	for (lp = bp->bits; !*lp; lp++)
		;

	u = 1;
	k = 0;
	for (; !(*lp & u); k++)
		u += u;

	*lp ^= u;

	if (!--bp->free) {
		pagedir[j] = bp->next;
		bp->next   = nil;
	}

	k  += (lp - bp->bits) * MBITS;
	k <<= bp->shift;

	if (ISOPT(OJUNK))
		c_mem_set((uchar *)bp->page + k, bp->size, JUNK);

	return (uchar *)bp->page + k;
}

static void *
imalloc(usize n)
{
	void *r;

	if ((n + mpagesize) < n || (n + mpagesize) >= (uintptr)pagedir)
		return nil;

	r = ((n <= mmaxsize) ? allocbytes : allocpages)(n);

	if (ISOPT(OZERO))
		c_mem_set(r, n, 0);

	return r;
}

static void *
irealloc(void *p, usize n)
{
	struct pginfo **mp;
	usize i, o, idx;
	void *np;

	idx = ptr2idx(p);

	/* too low or too high */
	if (idx < mpageshift || idx > lastidx )
		return nil;

	mp = &pagedir[idx];

	if (*mp == MFIRST) {
		/* modified (page-) pointer */
		if ((usize)(uintptr)p & mpagemask)
			return nil;
		for (o = mpagesize; *++mp == MFOLLOW; o += mpagesize)
			;
		if (!ISOPT(OREALLOC) && n <= o && n > (o - mpagesize)) {
			if (ISOPT(OJUNK))
				c_mem_set((uchar *)p+n, o-n, JUNK);
			return p;
		}
	} else if (*mp >= MMAGIC) {
		/* modified (chunk-) pointer */
		if ((usize)(uintptr)p & ((*mp)->size-1))
			return nil;

		i = ((usize)(uintptr)p & mpagemask) >> (*mp)->shift;

		/* chunk is already free */
		if ((*mp)->bits[i/MBITS] & (1UL << (i % MBITS)))
			return nil;

		o = (*mp)->size;

		if (!ISOPT(OREALLOC) &&
		    n <= o && (n > o / 2 || o == mminsize)) {
			if (ISOPT(OJUNK))
				c_mem_set((uchar *)p+n, o-n, JUNK);
			return p;
		}
	} else {
		/* pointer to wrong place */
		return nil;
	}

	if ((np = imalloc(n))) {
		if (n && o)
			c_mem_cpy(np, C_MIN(n, o), p);
		ifree(p);
	}

	return np;
}

static void
minit(void)
{
	char *p;
	int   e;

	e = errno;
	mpagesize = C_PAGESIZE;
	mpagemask = mpagesize - 1;
	for (mpageshift = 0; (1UL << mpageshift) != mpagesize; mpageshift++)
		;

	p = c_sys_getenv("MALLOC_OPTIONS");
	for (; p && *p; p++) {
		switch (*p) {
		case '>':
			mcache <<= 1;
			break;
		case '<':
			mcache >>= 1;
			break;
		case 'r':
			SETOPT(OREALLOC);
			break;
		case 'j':
			SETOPT(OJUNK);
			break;
		case 'z':
			SETOPT(OZERO);
			break;
		default:
			/* UNKNOWN CHAR */
			break;
		}
	}

	if (ISOPT(OZERO))
		SETOPT(OJUNK);

	if ((pagedir = MMAP(mpagesize)) == MAP_FAILED) {
		c_sys_write(2, "mmap(2) failed, check limits\n", 29);
		c_sys_abort();
	}

	morigo  = pageround((usize)(uintptr)segbrk(0)) >> mpageshift;
	morigo -= mpageshift;
	minfo   = mpagesize / sizeof(*pagedir);

	if (!mcache)
		mcache++;

	mcache <<= mpageshift;

	px = imalloc(sizeof(*px));
	errno = e;
}

void *
pubrealloc(void *p, usize n)
{
	void *r;

	r = nil;

	if (mact)
		goto invalid;

	mact++;

	if (!mstt) {
		if (p)
			goto invalid;
		minit();
		mstt++;
	}

	if (p == alloc0)
		goto invalid;

	if (!n) {
		if (p)
			ifree(p);
		r = alloc0;
	} else {
		r = p ? irealloc(p, n) : imalloc(n);
	}

	if (!r)
		errno = C_ENOMEM;

	mact--;
	return r;
invalid:
	errno = C_EINVAL;
	mact--;
	return r;
}
