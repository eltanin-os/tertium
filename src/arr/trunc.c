#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_arr_trunc(CArr *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n))
		return -1;

	if (m > c_arr_len(p, n))
		return 0;

	p->n = m*n;

	return 0;
}
