#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_feed(ctype_ioq *p)
{
	size r;

	if (p->mb->n)
		return p->mb->n;

	if ((r = (p->op)(p->fd, p->mb->p, p->mb->a)) <= 0)
		return r;

	p->mb->n = r;
	p->mb->a -= r;

	if (p->mb->a)
		c_mem_cpy(p->mb->p + p->mb->a, r, p->mb->p);

	return r;
}
