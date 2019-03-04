#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpush(CArr *p, void *v, usize m, usize n)
{
	usize *o;
	usize  ws;

	if (C_OFLW_UM(usize, m, n))
		return -1;

	m *= n;

	if (m > c_arr_avail(p))
		return -1;

	o = (void *)(uintptr)(p->p + sizeof(o) * 1);

	if (*o + m > p->a) {
		ws = p->a - *o;
		if (m + ws > c_arr_avail(p))
			return -1;
		p->n += ws;
		*o = sizeof(o) * 2;
	}

	c_mem_cpy(p->p + *o, m, v);
	p->n += m;
	*o   += m+1;
	p->p[*o-1] = 0;

	return 0;
}
