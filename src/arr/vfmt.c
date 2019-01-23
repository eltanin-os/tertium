#include <tertium/cpu.h>
#include <tertium/std.h>

static int
nomem(CFmt *p)
{
	return -1;
}

size
c_arr_vfmt(CArr *p, char *fmt, va_list args)
{
	CFmt f;
	size n;

	c_fmt_fdinit(&f, 0, p, nil);
	f.farg = nil;
	f.fn   = &nomem;

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
