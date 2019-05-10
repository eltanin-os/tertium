#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(CArr *p, usize m, usize n)
{
	if (c_dyn_ready(p, m, n) < 0)
		return nil;

	if (m > c_arr_bytes(p))
		p->n = m;

	return (p->p+m);
}
