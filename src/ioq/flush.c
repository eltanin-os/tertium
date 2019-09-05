#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_flush(CIoq *p)
{
	size r;

	r = c_sys_allrw(p->op, p->fd, p->mb->p, p->mb->n);
	p->mb->n = 0;
	return r;
}
