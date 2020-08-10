#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_vdiex(int r, char *fmt, va_list args)
{
	c_err_vwarnx(fmt, args);
	c_std_exit(r);
}
