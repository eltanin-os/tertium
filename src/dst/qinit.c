#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_dst_qinit(CArr *p, char *s, usize n)
{
	usize *o;
	c_arr_init(p, s, n);
	p->n = sizeof(o) * 2;
	/* start internal offset */
	o  = (void *)(uintptr)(p->p + sizeof(o) * 0);
	*o = p->n;
	o  = (void *)(uintptr)(p->p + sizeof(o) * 1);
	*o = p->n;
}
