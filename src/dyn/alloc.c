#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(CArr *p, usize m, usize n)
{
	usize a;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return nil;
	}

	m *= n;
	a  = p->a ? p->a : m >> 1;

	while (m > c_arr_avail(p)) {
		a *= 2;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return nil;
		p->a = a;
	}

	return (p->p+a);
}
