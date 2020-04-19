#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_fmt_print(ctype_fmt *p, char *fmt, ...)
{
	ctype_status r;
	va_list ap;

	va_start(ap, fmt);
	r = c_fmt_vprint(p, fmt, ap);
	va_end(ap);
	return r;
}
