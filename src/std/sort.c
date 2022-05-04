#include <tertium/cpu.h>
#include <tertium/std.h>

#define CMP(a, b, c) \
((a)->f((a)->p + ((b) * (a)->n), (a)->p + ((c) * (a)->n)))
#define SWAP(a, b, c) \
swap((a)->p + ((b) * (a)->n), (a)->p + ((c) * (a)->n), (a)->n)

struct sort {
	uchar *p;
	usize n;
	ctype_cmpfn f;
};

/* swap routines */
static void
swap(uchar *a, uchar *b, usize n)
{
	for (; n; --n, ++a, ++b) {
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}

/* merge routines */
static void
mrg(struct sort *p, uchar *buf, usize l, usize m, usize r)
{
	usize n1, n2;
	usize i, j, k;

	n1 = m - l; n2 = r - m;
	c_mem_cpy(buf, n1 * p->n, p->p + l * p->n);
	i = j = 0; k = l;
	while (i < n1 && j < n2) {
		if (p->f(buf + i * p->n, p->p + (m + j) * p->n) <= 0) {
			c_mem_cpy(p->p + k * p->n, p->n, buf + i * p->n);
			++i;
		} else {
			c_mem_cpy(p->p + k * p->n, p->n, p->p + (m + j) * p->n);
			++j;
		}
		++k;
	}
	c_mem_cpy(p->p + k * p->n, (n1 - i) * p->n, buf + i * p->n);
	k += (n1 - i);
	c_mem_cpy(p->p + k * p->n, (n2 - j) * p->n, p->p + (m + j) * p->n);
}

/* sort routines */
static void
isrt(struct sort *p, usize m)
{
	usize i, j;

	for (i = 0; i < m; ++i)
		for (j = i; j && CMP(p, j - 1, j) > 0; --j)
			SWAP(p, j, j - 1);
}

static void
recmsrt(struct sort *p, uchar *buf, usize l, usize r)
{
	usize m;

	if ((m = r - l) <= 1)
		return;
	m = l + (m >> 1);
	recmsrt(p, buf, l, m);
	recmsrt(p, buf, m, r);
	mrg(p, buf, l, m, r);
}

static void
msrt(struct sort *p, usize m)
{
	uchar *buf;

	if (!(buf = c_std_alloc(m >> 1, p->n))) {
		isrt(p, m); /* XXX */
		return;
	}
	recmsrt(p, buf, 0, m);
}

void
c_std_sort(void *v, usize m, usize n, ctype_cmpfn f)
{
	struct sort srt;

	if (C_STD_OVERFLOWM(usize, n, m))
		return;

	srt = (struct sort){v, n, f};

	if (m <= 16) {
		isrt(&srt, m);
		return;
	}

	msrt(&srt, m);
}
