#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_get(CArr *p, usize m, usize n)
{
	usize t;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return nil;
	}

	m *= n;
	t = m + n;

	if (t > c_arr_total(p)) {
		errno = C_ENOMEM;
		return nil;
	}

	if (t > c_arr_bytes(p))
		p->n = t;

	return (p->p + m);
}
