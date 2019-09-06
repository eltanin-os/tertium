#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_dyn_free(ctype_arr *p)
{
	p->a = 0;
	p->n = 0;
	c_std_free(p->p);
}
