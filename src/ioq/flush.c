#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_flush(ctype_ioq *p)
{
	size r;

	if ((r = c_std_allrw(p->op, p->fd, p->arr.p, p->arr.n)) < 0)
		return -1;

	c_arr_trunc(&p->arr, p->arr.n - r, sizeof(uchar));
	return 0;
}
