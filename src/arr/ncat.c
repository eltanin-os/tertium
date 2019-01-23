#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_arr_ncat(CArr *p, void *v, usize m, usize n)
{
	usize t;

	if (C_OFLW_UM(usize, m, n))
		return -1;

	t = m*n;

	if (t > c_arr_avail(p))
		return -1;

	c_mem_cpy(p->p + p->n, t, v);
	p->n += t;
	p->p[p->n] = '\0';

	return 0;
}

