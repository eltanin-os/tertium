#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dyn_cat(CArr *p, void *v, usize n)
{
	return c_dyn_ncat(p, v, n, sizeof(uchar));
}
