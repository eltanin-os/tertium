#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_dst_lfree(CNode *np, void (*f)(void *))
{
	if (f) f(np->p);
	c_std_free(np->p);
	c_std_free(np);
}
