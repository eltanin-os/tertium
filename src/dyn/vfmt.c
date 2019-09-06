#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
growbuffer(ctype_fmt *p)
{
	if (c_dyn_ready(p->mb, c_arr_total(p->mb) + 1, sizeof(uchar)) < 0)
		return -1;

	return 0;
}

size
c_dyn_vfmt(ctype_arr *p, char *fmt, va_list args)
{
	ctype_fmt f;
	size n;

	if (!c_arr_total(p))
		if (c_dyn_ready(p, C_DYNMINALLOC, sizeof(uchar)) < 0)
			return -1;

	c_fmt_fdinit(&f, 0, p, nil);
	f.farg = nil;
	f.fn = &growbuffer;

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
