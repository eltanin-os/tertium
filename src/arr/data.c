#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_data(CArr *p)
{
	return p->p;
}
