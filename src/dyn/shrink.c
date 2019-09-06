#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_shrink(ctype_arr *p)
{
	if (p->n == p->a)
		return 0;

	if (c_std_realloc(p->p, p->n, sizeof(uchar)))
		return -1;

	return 0;
}
