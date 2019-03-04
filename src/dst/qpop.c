#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpop(CArr *p, CArr *b, usize m, usize n)
{
	usize *o;

	if (C_OFLW_UM(usize, m, n))
		return -1;

	m *= n;
	o  = (void *)(uintptr)(p->p + sizeof(o) * 0);

	if (*o + m > p->a) {
		p->n -= p->a - *o;
		*o = sizeof(o) * 2;
	}

	if (m > c_arr_bytes(p))
		m = c_arr_bytes(p);

	if (c_arr_cat(b, p->p + *o, m, sizeof(uchar)) < 0)
		return -1;

	p->n -= m;
	*o   += m+1;

	return 0;
}
