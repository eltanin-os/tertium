#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_adt_lfree(ctype_node *np)
{
	c_std_free(np->p);
	c_std_free(np);
}
