#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_arr_init(Membuf *p, char *s, usize n)
{
	p->a = n;
	p->n = 0;
	p->p = (uchar *)s;
}
