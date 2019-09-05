#include <tertium/cpu.h>
#include <tertium/std.h>

#define F(j, m, k, r, f, v, n) \
((j) < (m) && ((k) >= (r) || (f)((v)+(n)*(j), (v)+(n)*(k))<=0))

static void
swap(uchar *a, uchar *b, usize n)
{
	uchar t;

	for (; n; n--) {
		t = *a;
		*a++ = *b;
		*b++ = t;
	}
}

static void
mrg(uchar *p, uchar *v, usize n, int (*f)(void *, void *), int l, int m, int r)
{
	int i, j, k;

	i = j = l;
	k = m;

	for (; i < r; i++)
		c_mem_cpy(p + n * i, n,
		    v + n * (F(j, m, k, r, f, v, n) ? j++ : k++));
}

static void
isrt(uchar *v, usize m, usize n, int (*f)(void *, void *))
{
	int i, j;

	i = 0;

	for (; i < (int)m; i++)
		for (j = i; j > 0 && f(v + n * (j - 1), v + n * j) > 0; j--)
			swap(v + n * j, v + n * (j - 1), n);
}

static void
msrt(uchar *v, usize m, usize n, int (*f)(void *, void *))
{
	usize i, j, t;
	uchar *p;

	/* TODO: stable fallback that requires O(1) additional space */
	if (!(p = c_std_alloc(m, n)))
		return;

	i = 1;
	t = m * n;

	for (; i < m; i *= 2) {
		for (j = 0; j < m; j += i * 2)
			mrg(p, v, n, f, j, C_MIN(j + i, m),
			    C_MIN(j + i * 2, m));
		c_mem_cpy(v, t, p);
	}
}

void
c_std_sort(void *v, usize m, usize n, int (*f)(void *, void *))
{
	if (C_OFLW_UM(usize, n, m))
		return;

	if (m < 32) {
		isrt(v, m, n, f);
		return;
	}

	msrt(v, m, n, f);
}
