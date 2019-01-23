#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_arr_cat(CArr *p, void *v, usize n)
{
	return c_arr_ncat(p, v, n, sizeof(uchar));
}

