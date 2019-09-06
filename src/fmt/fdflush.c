#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_fmt_fdflush(ctype_fmt *p)
{
	if (c_sys_allrw(p->op, (uintptr)p->farg, p->mb->p, p->mb->n) < 0)
		return -1;

	return 0;
}
