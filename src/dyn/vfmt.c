#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	return c_dyn_cat(p->farg, s, n, sizeof(uchar));
}

size
c_dyn_vfmt(ctype_arr *p, char *fmt, va_list args)
{
	ctype_fmt f;
	size r;
	c_fmt_init(&f, p, put);
	va_copy(f.args, args);
	r = c_fmt_fmt(&f, fmt);
	va_end(f.args);
	return r;
}
