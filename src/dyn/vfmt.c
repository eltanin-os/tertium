#include <tertium/cpu.h>
#include <tertium/std.h>

static int
growbuffer(CFmt *p)
{
	p->mb->a *= 2;
	if (!(p->mb->p = c_std_realloc(p->mb->p, p->mb->a, sizeof(uchar))))
		return -1;

	return 0;
}

size
c_dyn_vfmt(CArr *p, char *fmt, va_list args)
{
	CFmt f;
	size n;

	if (!p->a && !c_dyn_alloc(p, 64, sizeof(uchar)))
		return -1;

	c_fmt_fdinit(&f, 0, p, nil);
	f.farg = nil;
	f.fn   = &growbuffer;

	va_copy(f.args, args);
	n = c_fmt_fmt(&f, fmt);

	return n;
}
