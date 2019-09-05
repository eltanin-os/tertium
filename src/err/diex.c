#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_diex(int r, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	c_err_vdiex(r, fmt, ap);
	va_end(ap);
}
