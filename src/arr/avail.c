#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_avail(Membuf *p)
{
	return (p->a - p->n);
}

