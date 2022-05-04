#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	return c_dyn_cat(p->mb, s, n, sizeof(uchar));
}

size
c_dyn_vfmt(ctype_arr *p, char *fmt, va_list args)
{
	ctype_fmt f;

	if (c_dyn_ready(p, C_DYN_MINSIZ, sizeof(uchar)) < 0)
		return -1;

	c_fmt_init(&f, nil, p, put);
	va_copy(f.args, args);
	return c_fmt_fmt(&f, fmt);
}
