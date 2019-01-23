#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_fmt_fdinit(CFmt *p, int fd, CArr *mb, size (*fn)(int, void *, usize))
{
	p->mb    = mb;
	p->fn    = &c_fmt_fdflush;
	p->op    = fn;
	p->farg  = (void *)(uintptr)fd;
	p->nfmt  = 0;
	p->flags = 0;
	p->width = 0;
	p->prec  = 0;
}
