#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_fmt_fdinit(Fmt *p, int fd, Membuf *mb, size (*fn)(int, void *, usize))
{
	p->mb    = mb;
	p->fn    = &c_fmt_fdflush;
	p->op    = fn;
	p->farg  = (void *)(uintptr)fd;
	p->nfmt  = 0;
	p->flags = 0;
}
