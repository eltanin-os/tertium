#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_fmt_fdinit(ctype_fmt *p, ctype_fd fd, ctype_arr *mb, ctype_iofn fn)
{
	p->mb = mb;
	p->fn = &c_fmt_fdflush;
	p->op = fn;
	p->farg = (void *)(uintptr)fd;
	p->nfmt = 0;
	p->flags = 0;
	p->width = 0;
	p->prec = 0;
}
