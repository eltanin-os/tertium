#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_die(ctype_status eval, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	c_err_vdie(eval, fmt, ap);
	va_end(ap);
}
