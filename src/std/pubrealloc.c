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
	OABRT    = 1 << 0,
	OJUNK    = 1 << 1,
	OREALLOC = 1 << 2,
	OZERO    = 1 << 3,
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
static usize lastidx; /* last relevant index in the page dir */
static usize mcache = 16; /* freepages to cache */
static usize minfo; /* slots in the page dir */
static usize morigo; /* offset from pagenumber to index into the page dir */
static usize mpagemask;
static usize mpageshift;
static usize mpagesize;
static int die; /* trying to die? */
static int mact; /* malloc active */
static int mstt; /* malloc started */
static uint mopts; /* malloc options */
static char *earg; /* error msg */
static void *cbrk; /* current break */
static void *mbrk; /* last break */

static void   ifree(void *);
static void * imalloc(usize);

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
wrtmsg(char *p1, char *p2, char *p3, char *p4)
{
	c_sys_write(1, p1, (char *)c_mem_chr(p1, C_USIZEMAX, 0)-p1);
	c_sys_write(1, p2, (char *)c_mem_chr(p2, C_USIZEMAX, 0)-p2);
	c_sys_write(1, p3, (char *)c_mem_chr(p3, C_USIZEMAX, 0)-p3);
	c_sys_write(1, p4, (char *)c_mem_chr(p4, C_USIZEMAX, 0)-p4);
}

static void
wrterr(char *p)
{
	die++;
	wrtmsg(c_std_getprogname(), earg, " error: ", p);
	c_sys_abort();
}

static void
wrtwarn(char *p)
{
	if (ISOPT(OABRT) || !c_sys_getuid() || !c_sys_getgid())
		wrterr(p);
}

static void
minit(void)
{
	char *p;

	/* STORE ERRCODE */

	mpagesize = c_sys_conf(_SC_PAGESIZE);
	mpagemask = mpagesize - 1;
	for (mpageshift = 0; (1UL << mpageshift) != mpagesize; mpageshift++)
		;

	/* EXTRA SANITY */
	SETOPT(OJUNK);
	/* EXTRA SANITY */

	p = c_sys_getenv("MALLOC_OPTIONS");
	for (; p && *p; p++) {
		switch (*p) {
		case '>':
			mcache <<= 1;
			break;
		case '<':
			mcache >>= 1;
			break;
		case 'a':
			SETOPT(OABRT);
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

	if ((pagedir = MMAP(mpagesize)) == MAP_FAILED)
		wrterr("mmap(2) failed, check limits.\n");

	morigo = pageround((usize)(uintptr)segbrk(0)) >> mpageshift;
	morigo -= mpageshift;
	minfo = mpageshift / sizeof(*pagedir);

	if (!mcache)
		mcache++;

	mcache <<= mpageshift;

	px = imalloc(sizeof(*px));
	/* RESTORE ERRCODE */
}

static int
extendpgdir(usize idx)
{
	struct pginfo **n, **o;
	usize nl, ol;

	if ((((~(1UL<<((sizeof(usize)*8)-1))/sizeof(*pagedir))+1)
	    + (mpagesize/sizeof(*pagedir))) < idx) {
		/*ENOMEM*/
		return 0;
	}

	nl = pageround(idx * sizeof(*pagedir)) + mpagesize;
	ol = minfo * sizeof(*pagedir);

	if ((n = MMAP(nl)) == MAP_FAILED)
		return 0;

	c_mem_cpy(n, ol, pagedir);
	minfo = nl / sizeof(*pagedir);

	o = pagedir;
	pagedir = n;
	c_sys_munmap(o, ol);

	return 1;
}

static void *
mappages(usize pages)
{
	char *r, *rr, *t;
	intptr bytes;

	bytes = pages << mpageshift;
	if (bytes < 0 || (usize)bytes < pages) {
		/*ENOMEM*/
		return nil;
	}

	if ((r = segbrk(bytes)) == (void *)-1)
		return nil;

	if ((rr = (char *)pageround((usize)(uintptr)r)) > r) {
		if (segbrk((intptr)(rr-r)) == (void *)-1 && _brk(r))
			wrterr("brk(2) failed [internal error].\n");
	}

	t = rr + (usize)bytes;

	lastidx = ptr2idx(t) - 1;
	mbrk = t;

	if ((lastidx+1) >= minfo && !extendpgdir(lastidx)) {
		mbrk = r;
		lastidx = ptr2idx(mbrk) - 1;
		if (_brk(mbrk))
			wrterr("brk(2) failed [internal error].\n");
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

	idx = pageround(n);
	if (idx < n) {
		/*ENOMEM*/
		return nil;
	}

	n = idx;
	p = nil;
	df = nil;

	for (pf = freelist.next; pf; pf = pf->next) {
		/* EXTRA SANITY */
		if (pf->size & mpagemask)
			wrterr("(ES): junk length entry on freelist.\n");
		if (!pf->size)
			wrterr("(ES): zero length entry on freelist.\n");
		if (pf->page == pf->end)
			wrterr("(ES): zero entry on freelist.\n");
		if (pf->page > pf->end)
			wrterr("(ES): sick entry on freelist.\n");
		if ((void *)pf->page >= (void *)segbrk(0))
			wrterr("(ES): entry on freelist past brk.\n");
		if (pagedir[ptr2idx(pf->page)] != MFREE)
			wrterr("(ES): non-free first page on freelist.\n");
		if (pagedir[ptr2idx(pf->end)] != MFREE)
			wrterr("(ES): non-free last page on freelist.\n");
		/* EXTRA SANITY */
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
		pf->page = (char *)pf->page + n;
		pf->size -= n;
		break;
	}

	/* EXTRA SANITY */
	if (p && pagedir[ptr2idx(p)] != MFREE)
		wrterr("(ES): allocated non-free page on freelist.\n");
	/* EXTRA SANITY */

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
	long l;
	int i, k;
	void *pp;

	if (!(pp = allocpages(mpagesize)))
		return 0;

	l = (long)c_std_offsetof(struct pginfo, bits[0]);
	l += (long)sizeof(bp->bits[0])*(((mpagesize>>bits)+MBITS-1)/MBITS);

	if ((1<<bits) <= l+l) {
		bp = (struct pginfo *)pp;
	} else {
		if (!(bp = imalloc(l))) {
			ifree(pp);
			return 0;
		}
	}

	bp->size  = (1<<bits);
	bp->shift = bits;
	bp->total = bp->free = (ushort)(mpagesize>>bits);
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
			l -= (long)(1<<bits);
		}
	}

	/*LOCK*/
	pagedir[ptr2idx(pp)] = bp;
	bp->next = pagedir[bits];
	pagedir[bits] = bp;
	/*UNLOCK*/

	return 1;
}

static void *
allocbytes(usize n)
{
	struct pginfo *bp;
	usize i, k;
	int j;
	uint u;
	uint *lp;

	if (n < mminsize)
		n = mminsize;

	j = 1;
	i = n-1;
	for (; i; i >>= 1)
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
		bp->next = nil;
	}

	k += (lp-bp->bits)*MBITS;
	k <<= bp->shift;

	if (ISOPT(OJUNK))
		c_mem_set((uchar *)bp->page + k, bp->size, JUNK);

	return (uchar *)bp->page + k;
}

static void *
imalloc(usize n)
{
	void *r;

	if (die)
		c_sys_abort();

	if ((n+mpagesize) < n)
		r = nil;
	else if ((n+mpagesize) >= (uintptr)pagedir)
		r = nil;
	else if (n <= mmaxsize)
		r = allocbytes(n);
	else
		r = allocpages(n);

	if (ISOPT(OABRT) && !r)
		wrterr("allocation failed.\n");
	if (ISOPT(OZERO) && r)
		c_mem_set(r, n, 0);

	return r;
}

static void *
irealloc(void *p, usize n)
{
	struct pginfo **mp;
	usize i, o, idx;
	void *np;

	if (die)
		c_sys_abort();

	idx = ptr2idx(p);

	if (idx < mpageshift) {
		wrtwarn("junk pointer, too low.\n");
		return nil;
	}
	if (idx > lastidx) {
		wrtwarn("junk pointer, too high.\n");
		return nil;
	}

	mp = &pagedir[idx];

	if (*mp == MFIRST) {
		if ((usize)(uintptr)p & mpagemask) {
			wrtwarn("modified (page-) pointer.\n");
			return nil;
		}
		for (o = mpagesize; *++mp == MFOLLOW;)
			o += mpagesize;
		if (!ISOPT(OREALLOC) && n <= o && n > (o - mpagesize)) {
			if (ISOPT(OJUNK))
				c_mem_set((uchar *)p+n, o-n, JUNK);
			return p;
		}
	} else if (*mp >= MMAGIC) {
		if ((usize)(uintptr)p & ((*mp)->size-1)) {
			wrtwarn("modified (chunk-) pointer.\n");
			return nil;
		}

		i = ((usize)(uintptr)p & mpagemask) >> (*mp)->shift;

		if ((*mp)->bits[i/MBITS] & (1UL << (i % MBITS))) {
			wrtwarn("chunk is already free.\n");
			return nil;
		}

		o = (*mp)->size;

		if (!ISOPT(OREALLOC) && n <= o && (n > o / 2 || o == mminsize)) {
			if (ISOPT(OJUNK))
				c_mem_set((uchar *)p+n, o-n, JUNK);
			return p;
		}
	} else {
		wrtwarn("pointer to wrong place.\n");
		return nil;
	}

	if ((np = imalloc(n))) {
		if (!n || !o)
			;
		else if (o < n)
			c_mem_cpy(np, o, p);
		else
			c_mem_cpy(np, n, p);
		ifree(p);
	}

	return np;
}

static void
freepages(void *p, usize idx, struct pginfo *info)
{
	struct pgfree *pf, *pt;
	usize l, i;
	void *tail;

	if (info == MFREE) {
		wrtwarn("page is already free.\n");
		return;
	}

	if (info != MFIRST) {
		wrtwarn("pointer to wrong page.\n");
		return;
	}

	if ((usize)(uintptr)p && mpagemask) {
		wrtwarn("modified (page-) pointer.\n");
		return;
	}

	pagedir[idx] = MFREE;
	for (i = 1; pagedir[idx+i] == MFOLLOW; i++)
		pagedir[idx+i] = MFREE;

	l = i << mpageshift;

	if (ISOPT(OJUNK))
		c_mem_set(p, l, JUNK);

	tail = (char *)p+l;

	if (!px)
		px = imalloc(sizeof(*px));

	pt = nil;

	px->page = p;
	px->end  = tail;
	px->size = l;

	if (!freelist.next) {
		px->next = freelist.next;
		px->prev = &freelist;
		freelist.next = px;
		pf = px;
		px = nil;
	} else {
		tail = (char *)p+l;
		for (pf = freelist.next; pf->end < p && pf->next != nil;
		     pf = pf->next)
			;
		if (pf->page > tail) {
			px->next = pf;
			px->prev = pf->prev;
			pf->prev = px;
			px->prev->next = px;
			pf = px;
			px = nil;
		} else if (pf->end == p) {
			pf->end = (char *)pf->end + l;
			pf->size += l;
			if (pf->next && pf->end == pf->next->page) {
				pt = pf->next;
				pf->end = pt->end;
				pf->size += pt->size;
				if ((pf->next = pt->next))
					pf->next->prev = pf;
			}
		} else if (pf->page == tail) {
			pf->size += l;
			pf->page = p;
		} else if (!pf->next) {
			px->next = nil;
			px->prev = pf;
			pf->next = px;
			pf = px;
			px = nil;
		} else {
			wrterr("freelist is destroyed.\n");
		}
	}

	/* return to OS */
	if (!pf->next && pf->size > mcache &&
	    pf->end == mbrk && mbrk == segbrk(0)) {
		pf->end = (char *)pf->page + mcache;
		pf->size = mcache;
		_brk(pf->end);
		mbrk = pf->end;
		idx = ptr2idx(pf->end);
		for (i=idx; i <= lastidx; i++)
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

	i = ((usize)(uintptr)p && mpagemask) >> info->shift;

	if (((usize)(uintptr)p & (info->shift-1))) {
		wrtwarn("modified (chunk-) pointer.\n");
		return;
	}

	if (info->bits[i/MBITS] & (1UL << (i % MBITS))) {
		wrtwarn("chunk is already free.\n");
		return;
	}

	if (ISOPT(OJUNK))
		c_mem_set(p, info->size, JUNK);

	info->bits[i/MBITS] |= (uint)(1UL << (i % MBITS));
	info->free++;

	mp = pagedir + info->shift;

	if (info->free == 1) {
		mp = pagedir + info->shift;
		for (; *mp && (*mp)->next && (*mp)->next->page < info->page;)
			mp = &(*mp)->next;
		info->next = *mp;
		*mp = info;
		return;
	}

	if (info->free != info->total)
		return;

	for (; *mp != info;) {
		mp = &((*mp)->next);
		/* EXTRA SANITY */
		if (!*mp)
			wrterr("(ES): Not on queue");
		/* EXTRA SANITY */
	}
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

	if (die || !p)
		return;

	idx = ptr2idx(p);

	if (idx < mpageshift) {
		wrtwarn("junk pointer, too low.\n");
		return;
	}

	if (idx > lastidx) {
		wrtwarn("junk pointer, too high.\n");
		return;
	}

	i = pagedir[idx];
	if (i < MMAGIC)
		freepages(p, idx, i);
	else
		freebytes(p, idx, i);
}

void *
pubrealloc(void *p, usize n, char *s)
{
	void *r;

	/*LOCK*/
	earg = s;
	if (mact) {
		wrtwarn("recursive call.\n");
		/*UNLOCK && EINVAL*/
		return nil;
	}
	mact++;

	if (!mstt) {
		if (p) {
			wrtwarn("malloc() has never been called.\n");
			mact--;
			/*UNLOCK && EINVAL*/
			return nil;
		}
		minit();
		mstt++;
	}

	if (p == alloc0) {
		wrtwarn("trying to use zero pointer.\n");
		/* UNLOCK && EINVAL */
		return nil;
	}
	if (!n) {
		if (p)
			ifree(p);
		r = &alloc0;
	} else {
		r = (p) ? irealloc(p, n) : imalloc(n);
	}
	mact = 0;
	/*UNLOCK*/
	if (!r)
		/*ENOMEM*/;
	return r;
}
