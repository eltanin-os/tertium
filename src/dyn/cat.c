#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dyn_cat(Membuf *p, void *v, usize n)
{
	usize a;

	a = c_arr_avail(p) ? p->a : n;

	for (; n > c_arr_avail(p);) {
		a *= 2;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return -1;
		p->a = a;
	}

	c_mem_cpy(p->p + p->n, n, v);
	p->n += n;
	p->p[p->n] = '\0';

	return 0;
}
