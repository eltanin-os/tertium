#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_free(ctype_ioq *p)
{
	c_dyn_free(&p->arr);
	c_std_free(p);
}
