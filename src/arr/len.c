#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_arr_len(Membuf *p, usize n)
{
	return (p->n / n);
}
