#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_trunc(ctype_arr *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	m *= n;

	if (m > c_arr_bytes(p))
		return 0;

	p->n = m;
	p->p[p->n] = 0;

	return 0;
}
