#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_vdie(ctype_status eval, char *fmt, va_list args)
{
	c_err_vwarn(fmt, args);
	c_std_exit(eval);
}
