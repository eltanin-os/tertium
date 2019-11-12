#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_flush(ctype_ioq *p)
{
	size r;

	if ((r = c_std_allrw(p->op, p->fd, p->mb->p, p->mb->n)) < 0)
		return -1;

	c_arr_trunc(p->mb, c_arr_bytes(p->mb) - r, sizeof(uchar));

	return 0;
}
