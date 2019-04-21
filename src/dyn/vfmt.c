#include <tertium/cpu.h>
#include <tertium/std.h>

static int
growbuffer(CFmt *p)
{
	if (!c_dyn_alloc(p->mb, c_arr_total(p->mb)+1, sizeof(uchar)))
		return -1;

	return 0;
}

size
c_dyn_vfmt(CArr *p, char *fmt, va_list args)
{
	CFmt f;
	size n;

	if (!p->a)
		if (!c_dyn_alloc(p, C_DYNMINALLOC, sizeof(uchar)))
			return -1;

	c_fmt_fdinit(&f, 0, p, nil);
	f.farg = nil;
	f.fn   = &growbuffer;

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
