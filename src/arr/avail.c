#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_avail(ctype_arr *p)
{
	return (p->a - p->n);
}
