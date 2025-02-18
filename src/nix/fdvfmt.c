#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
put(ctype_fmt *p, char *s, usize n)
{
	return c_nix_allrw(&c_nix_fdwrite, *(ctype_fd *)p->farg, s, n);
}

ctype_status
c_nix_fdvfmt(ctype_fd fd, char *fmt, va_list ap)
{
	ctype_fmt f;
	size r;
	c_fmt_init(&f, &fd, put);
	va_copy(f.args, ap);
	r = c_fmt_fmt(&f, fmt);
	va_end(ap);
	return -(r < 0);
}
