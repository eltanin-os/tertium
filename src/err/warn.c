#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_err_warn(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	c_err_vwarn(fmt, ap);
	va_end(ap);
	return 1;
}
