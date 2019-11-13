#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	return c_ioq_nput(p->farg, s, n);
}

size
c_ioq_vfmt(ctype_ioq *p, char *fmt, va_list args)
{
	ctype_fmt f;

	c_fmt_init(&f, p, &p->arr, put);
	va_copy(f.args, args);
	return c_fmt_fmt(&f, fmt);
}
