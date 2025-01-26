#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_fmt_vprint(ctype_fmt *p, char *fmt, va_list ap)
{
	ctype_fmt f;
	size r;
	c_fmt_init(&f, p->farg, p->func);
	va_copy(f.args, ap);
	r = c_fmt_fmt(&f, fmt);
	va_end(f.args);
	return -(r < 0);
}
