#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_str_fmt(char **sp, char *fmt, ...)
{
	va_list ap;
	size r;
	va_start(ap, fmt);
	r = c_str_vfmt(sp, fmt, ap);
	va_end(ap);
	return r;
}
