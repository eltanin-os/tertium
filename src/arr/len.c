#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_len(ctype_arr *p, usize n)
{
	return (n ? (p->n / n) : 0);
}
