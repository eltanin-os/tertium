#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_fmt(CIoq *p, char *fmt, ...)
{
	va_list ap;
	size n;

	va_start(ap, fmt);
	n = c_ioq_vfmt(p, fmt, ap);
	va_end(ap);

	return n;
}
