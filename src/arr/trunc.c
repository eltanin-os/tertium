#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_trunc(ctype_arr *p, usize m, usize n)
{
	if (C_STD_OVERFLOWM(usize, m, n)) {
		errno = C_ERR_EOVERFLOW;
		return -1;
	}

	if (c_arr_bytes(p) <= (m *= n)) return 0;
	p->n = m;
	if (p->p) p->p[p->n] = 0;
	return 0;
}
