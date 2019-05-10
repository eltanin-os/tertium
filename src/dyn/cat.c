#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_dyn_cat(CArr *p, void *v, usize m, usize n)
{
	if (!m)
		return 0;

	if (c_dyn_ready(p, m, n) < 0)
		return -1;

	m *= n;
	c_mem_cpy((uchar *)c_arr_data(p) + c_arr_bytes(p), m, v);
	p->n += m;
	p->p[p->n] = 0;

	return m;
}
