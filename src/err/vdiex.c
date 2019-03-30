#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_err_vdiex(int r, char *fmt, va_list args)
{
	c_ioq_fmt(ioq2, "%s: ", c_std_getprogname());
	if (fmt)
		c_ioq_vfmt(ioq2, fmt, args);
	c_ioq_put(ioq2, "\n");
	c_std_exit(r);
}
