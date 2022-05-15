#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_fmt_init(ctype_fmt *p, void *farg, ctype_fmtopfn func)
{
	p->func = func;
	p->farg = farg;
	p->nfmt = 0;
	p->flags = 0;
	p->width = 0;
	p->prec = 0;
}
