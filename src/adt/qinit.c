#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_adt_qinit(CQueue *p, char *s, usize n)
{
	c_arr_init(&p->mb, s, n);
	p->h = 0;
}
