#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_vfmt(Ioq *p, char *fmt, va_list args)
{
	Fmt f;
	size n;

	c_fmt_fdinit(&f, p->fd, p->mb, p->op);

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
