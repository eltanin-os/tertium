#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
nomem(ctype_fmt *p)
{
	(void)p;
	errno = C_ENOMEM;
	return -1;
}

size
c_arr_vfmt(ctype_arr *p, char *fmt, va_list args)
{
	ctype_fmt f;
	size n;

	c_fmt_fdinit(&f, 0, p, nil);
	f.farg = nil;
	f.fn = &nomem;

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
