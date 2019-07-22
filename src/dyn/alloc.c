#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_dyn_alloc(CArr *p, usize m, usize n)
{
	usize t;

	if (c_dyn_ready(p, m, n) < 0)
		return nil;

	m *= n;
	t  = m+n;

	if (t > c_arr_bytes(p))
		p->n = t;

	return p->p + m;
}
