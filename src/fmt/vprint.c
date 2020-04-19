#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	return c_arr_cat(p->mb, s, n, sizeof(uchar));
}

ctype_status
c_fmt_vprint(ctype_fmt *p, char *fmt, va_list ap)
{
	ctype_fmt f;

	c_fmt_init(&f, nil, p->mb, put);
	va_copy(f.args, ap);
	return c_fmt_fmt(&f, fmt);
}
