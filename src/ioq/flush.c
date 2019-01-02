#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_flush(Ioq *p)
{
	(p->op)(p->fd, p->mb->p, p->mb->n);
	p->mb->n = 0;
	return 0;
}
