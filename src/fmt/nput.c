#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
__fmt_trycat(ctype_fmt *p, char *s, usize n)
{
	if (p->func(p, s, n) < 0)
		return -1;

	p->nfmt += n;
	return 0;
}

static ctype_status
pad(ctype_fmt *p, usize n)
{
	int w;

	for (w = p->width - n; w > 0; --w)
		if (__fmt_trycat(p, " ", 1) < 0)
			return -1;

	return 0;
}

ctype_status
c_fmt_nput(ctype_fmt *p, char *s, usize n)
{
	if (!s)
		s = "<nil>";

	if ((p->flags & C_FMTPREC) && n > (usize)p->prec)
		n = p->prec;

	if (!(p->flags & C_FMTLEFT) && pad(p, n) < 0)
		return -1;

	if (__fmt_trycat(p, s, n) < 0)
		return -1;

	if ((p->flags & C_FMTLEFT) && pad(p, n) < 0)
		return -1;

	return 0;
}
