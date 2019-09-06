#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_flush(ctype_ioq *p)
{
	if (c_sys_allrw(p->op, p->fd, p->mb->p, p->mb->n) < 0)
		return -1;

	return 0;
}
