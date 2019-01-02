#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_get(Membuf *p, usize m, usize n)
{
	usize t;

	if (n && m > (usize)-1/n)
		return nil;

	t = m*n;

	if (t > c_arr_avail(p))
		return nil;

	return (p->p+t);
}
