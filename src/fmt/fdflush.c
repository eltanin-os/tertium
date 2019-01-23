#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_fmt_fdflush(CFmt *p)
{
	(p->op)((uintptr)p->farg, p->mb->p, p->mb->n);
	p->mb->n = 0;
	return 0;
}
