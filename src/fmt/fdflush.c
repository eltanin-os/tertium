#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_fmt_fdflush(ctype_fmt *p)
{
	size r;

	if ((r = c_sys_allrw(p->op, (uintptr)p->farg, p->mb->p, p->mb->n)) < 0)
		return -1;

	c_arr_trunc(p->mb, c_arr_bytes(p->mb) - r, sizeof(uchar));

	return 0;
}
