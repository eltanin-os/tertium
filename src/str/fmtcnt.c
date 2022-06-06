#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_str_fmtcnt(char *fmt, ...)
{
	va_list ap;
	usize r;
	va_start(ap, fmt);
	r = c_str_vfmtcnt(fmt, ap);
	va_end(ap);
	return r;
}
