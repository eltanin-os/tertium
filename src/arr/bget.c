#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_bget(CArr *p, usize n)
{
	return c_arr_get(p, n, sizeof(uchar));
}
