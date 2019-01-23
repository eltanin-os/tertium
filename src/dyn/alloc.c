#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(CArr *p, usize m, usize n)
{
	usize a, t;

	if (C_OFLW_UM(usize, m, n))
		return nil;

	t = m*n;
	a = c_arr_avail(p) ? p->a : t;

	for (; t > c_arr_avail(p);) {
		a *= 2;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return nil;
		p->a = a;
	}

	return (p->p+t);
}
