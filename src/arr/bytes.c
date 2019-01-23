#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_bytes(CArr *p)
{
	return c_arr_len(p, sizeof(uchar));
}
