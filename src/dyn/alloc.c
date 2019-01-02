#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(Membuf *p, usize m, usize n)
{
	usize a, t;

	if (n && m > (usize)-1/n)
		return nil;

	t = m*n;
	a = c_arr_avail(p) ? p->a : t;

	for (; t > c_arr_avail(p);) {
		a *= 2;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return nil;
	}
	p->a = a;

	return (p->p+t);
}
