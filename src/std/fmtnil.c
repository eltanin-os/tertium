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
c_std_fmtnil(char *fmt, ...)
{
	ctype_fmt f;
	va_list ap;
	usize n;

	va_start(ap, fmt);
	c_fmt_init(&f, nil, nil, put);
	va_copy(f.args, ap);
	n = c_fmt_fmt(&f, fmt);
	va_end(ap);

	return n;
}
