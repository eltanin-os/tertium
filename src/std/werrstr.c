#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_std_werrstr(char *fmt, ...)
{
	ctype_arr arr;
	va_list ap;
	char buf[C_IOQ_ERRSIZ];

	c_arr_init(&arr, buf, sizeof(buf));
	va_start(ap, fmt);
	c_arr_vfmt(&arr, fmt, ap);
	va_end(ap);
	c_std_errstr(buf, sizeof(buf));
}
