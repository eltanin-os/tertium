#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_vdiex(ctype_status eval, char *fmt, va_list args)
{
	c_err_vwarnx(fmt, args);
	c_std_exit(eval);
}
