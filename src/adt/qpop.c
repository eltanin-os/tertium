#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_adt_qpop(ctype_node **sp)
{
	return c_adt_lpop(sp);
}
