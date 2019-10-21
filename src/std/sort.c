#include <tertium/cpu.h>
#include <tertium/std.h>

static inline void
swap(uchar *a, uchar *b, usize n)
{
	for (; n; --n, ++a, ++b) {
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}

static void
isrt(uchar *v, usize m, usize n, ctype_cmpfn f)
{
	usize i, j;

	for (i = 0; i < m; ++i)
		for (j = i; j && f(v + (j - 1) * n, v + j * n) > 0; --j)
			swap(v + j * n, v + (j - 1) * n, n);
}

static void
mrg(uchar *p, int l, int m, int r, uchar *v, usize n, ctype_cmpfn f)
{
	int idx[2], x;

	idx[0] = l;
	idx[1] = m;

	for (; l < r; ++l) {
		x = !(idx[0] < m &&
		    (idx[1] >= r || f(v + idx[0] * n, v + idx[1] * n) <= 0));
		c_mem_cpy(p + l * n, n, v + idx[x] * n);
		++idx[x];
	}
}

static void
msrt(uchar *v, usize m, usize n, ctype_cmpfn f)
{
	usize i, j;
	usize t;
	uchar *p;

	if ((t = m * n) <= C_BIOSIZ) {
		p = __builtin_alloca(t);
	} else if (!(p = c_std_alloc(m, n))) {
		isrt(v, m, n, f); /* TODO: fast fallback */
		return;
	}

	for (i = 1; i < m; i <<= 1) {
		for (j = 0; j < m; j += i << 1)
			mrg(p, j, C_MIN(j + i, m), C_MIN(j + (i << 1), m),
			    v, n, f);
		c_mem_cpy(v, t, p);
	}
	c_std_free(p);
}

void
c_std_sort(void *v, usize m, usize n, ctype_cmpfn f)
{
	if (C_OFLW_UM(usize, n, m))
		return;

	if (m <= 12) {
		isrt(v, m, n, f);
		return;
	}

	msrt(v, m, n, f);
}
