#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *
c_adt_lnew(void *v, usize n)
{
	void *p;

	if (!(p = c_std_alloc(n, sizeof(uchar))))
		return nil;
	return c_mem_cpy(p, n, v);
}
