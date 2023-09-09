#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_arr_fmt(ctype_arr *p, char *fmt, ...)
{
	va_list ap;
	size n;
	va_start(ap, fmt);
	n = c_arr_vfmt(p, fmt, ap);
	va_end(ap);
	return n;
}
