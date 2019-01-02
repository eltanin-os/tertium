#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dyn_cat(Membuf *p, void *v, usize m, usize n)
{
	usize a, t;

	if (n && m > (usize)-1/n)
		return -1;

	t = m*n;
	a = c_arr_avail(p) ? p->a : t;

	for (; t > c_arr_avail(p);) {
		a *= 2;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return -1;
	}
	p->a = a;
	c_mem_cpy(p->p + p->n, v, t);
	p->p[p->n] = '\0';

	return 0;
}
