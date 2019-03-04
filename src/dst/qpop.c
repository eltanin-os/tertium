#include <tertium/cpu.h>
#include <tertium/std.h>

#define POSOIDX (sizeof(o) * 2)

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
		*o    = POSOIDX;
	}

	if (c_arr_bytes(p) == POSOIDX)
		return 0;

	m = (m > c_arr_bytes(p) - POSIDX) ? c_arr_bytes(p) - POSOIDX : m;

	if (c_arr_cat(b, p->p + *o, m, sizeof(uchar)) < 0)
		return -1;

	p->n -= m;
	*o   += m+1;

	return 0;
}
