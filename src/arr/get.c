#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_get(CArr *p, usize m, usize n)
{
	usize t;

	if (C_OFLW_UM(usize, m, n))
		return nil;

	t = m*n;

	if (t > c_arr_avail(p))
		return nil;

	return (p->p+t);
}
