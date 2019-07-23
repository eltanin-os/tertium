#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dyn_shrink(CArr *p)
{
	if (p->n == p->a)
		return 0;

	if (c_std_realloc(p->p, p->n, sizeof(uchar)))
		return -1;

	return 0;
}
