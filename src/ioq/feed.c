#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_feed(ctype_ioq *p)
{
	size r;

	if (p->arr.n)
		return p->arr.n;

	if ((r = (p->op)(p->fd, p->arr.p, p->arr.a)) <= 0)
		return r;

	p->arr.n = r;
	p->arr.a -= r;
	if (p->arr.a)
		c_mem_cpy(p->arr.p + p->arr.a, p->arr.p, r);

	return r;
}
