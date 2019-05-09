#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(CArr *p, usize m, usize n)
{
	usize a, t;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return nil;
	}

	m *= n;
	t  = m+n;
	a  = p->a ? p->a : t;

	while (t > c_arr_avail(p)) {
		a <<= 1;
		if (!(p->p = c_std_realloc(p->p, a, sizeof(uchar))))
			return nil;
		p->a = a;
	}

	if (m > c_arr_bytes(p))
		p->n = m;

	return (p->p+m);
}
