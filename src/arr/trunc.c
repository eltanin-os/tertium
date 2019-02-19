#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_arr_trunc(CArr *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n))
		return -1;

	m *= n;

	if (m > c_arr_bytes(p))
		return 0;

	p->n = m;

	return 0;
}
