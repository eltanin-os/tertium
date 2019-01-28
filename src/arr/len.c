#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_len(CArr *p, usize n)
{
	return (n ? (p->n / n) : 0);
}
