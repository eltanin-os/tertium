#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_dyn_cat(CArr *p, void *v, usize m, usize n)
{
	usize t;

	if (C_OFLW_UM(usize, m, n))
		return -1;

	t = m*n;
	p->a = c_arr_avail(p) ? p->a : t;

	while (t > c_arr_avail(p)) {
		p->a *= 2;
		if (!(p->p = c_std_realloc(p->p, p->a, sizeof(uchar))))
			return -1;
	}

	c_mem_cpy(p->p + p->n, t, v);
	p->n += t;
	p->p[p->n] = '\0';

	return t;
}
