#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_vdie(int r, char *fmt, va_list args)
{
	c_err_vwarn(fmt, args);
	c_std_exit(r);
}
