#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dyn_ncat(Membuf *p, void *v, usize m, usize n)
{
	usize t;

	if (OFLW_UM(usize, m, n))
		return -1;

	t = m*n;
	p->a = c_arr_avail(p) ? p->a : t;

	for (; t > c_arr_avail(p);) {
		p->a *= 2;
		if (!(p->p = c_std_realloc(p->p, p->a, sizeof(uchar))))
			return -1;
	}

	c_mem_cpy(p->p + p->n, t, v);
	p->n += t;
	p->p[p->n] = '\0';

	return 0;
}
