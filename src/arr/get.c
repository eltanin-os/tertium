#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_get(ctype_arr *p, usize m, usize n)
{
	usize t;

	if (C_STD_OVERFLOWM(usize, m, n)) {
		errno = C_ERR_EOVERFLOW;
		return nil;
	}
	m *= n;
	if ((t = m + n) > c_arr_total(p)) {
		errno = C_ERR_ENOMEM;
		return nil;
	}

	if (t > c_arr_bytes(p))
		p->n = t;

	return (p->p + m);
}
