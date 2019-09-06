#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_vfmt(ctype_ioq *p, char *fmt, va_list args)
{
	ctype_fmt f;
	size n;

	c_fmt_fdinit(&f, p->fd, p->mb, p->op);

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
