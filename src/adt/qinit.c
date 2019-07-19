#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_adt_qinit(CQueue *p, char *s, usize n)
{
	p->a = n;
	p->h = 0;
	p->t = 0;
	p->p = (uchar *)s;
}
