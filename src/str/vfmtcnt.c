#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	(void)p;
	(void)s;
	(void)n;
	return 0;
}

usize
c_str_vfmtcnt(char *fmt, va_list ap)
{
	ctype_fmt f;
	size r;
	c_fmt_init(&f, nil, put);
	va_copy(f.args, ap);
	r = c_fmt_fmt(&f, fmt);
	va_end(f.args);
	return r;
}
