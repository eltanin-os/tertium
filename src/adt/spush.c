#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_spush(ctype_node **sp, void *v, usize n)
{
	return c_adt_lpush(sp, c_adt_lnew(v, n));
}
