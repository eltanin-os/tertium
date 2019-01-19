#include <tertium/cpu.h>
#include <tertium/std.h>

#include "verb.h"

static int
fmtfmt(Fmt *f, uchar *s)
{
	struct fmtverb *p;
	usize n;
	int i;

	n = c_arr_len(&Fmts, sizeof(*p));

	for (;;) {
		i = 0;
		f->r = *s;
		for (; i <= n; i++) {
			p = c_arr_get(&Fmts, i, sizeof(*p));
			if (p->c == *s) {
				for (; !(p->f); )
					;
				return (p->f)(f);
			}
		}

		i = 0;
		for (;;) {
			if (!(p = &VFmts[i++]))
				break;
			if (p->c == *s) {
				c_fmt_install(p->c, p->f);
				return (p->f)(f);
			}
		}
	}
}

static int
fmtflag(Fmt *f, uchar *s)
{
	int i, r, nfmt;

	nfmt = 0;

	for (;;) {
		nfmt++;
		if (!(f->r = *++s))
			return -1;

		switch (f->r) {
		case '.':
			f->flags = FmtWidth|FmtPrec;
			continue;
		case '0':
			if (!(f->flags & FmtWidth)) {
				f->flags |= FmtZero;
				continue;
			}
			/* FALLTHROUGH */
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			i = 0;
			for (; *s >= '0' && *s <= '9'; nfmt++, s++)
				i = i * 10 + *s - '0';
			s--; nfmt--;
numflag:
			if (f->flags & FmtWidth) {
				f->flags |= FmtPrec;
				f->prec = i;
			} else {
				f->flags |= FmtWidth;
				f->width = i;
			}
			continue;
		case '*':
			if ((i = va_arg(f->args, int)) < 0) {
				if (f->flags & FmtPrec) {
					f->flags &= ~FmtPrec;
					f->prec = 0;
					continue;
				}
				i = -i;
				f->flags |= FmtLeft;
			}
			goto numflag;
		}

		if ((r = fmtfmt(f, s)) < 0)
			return -1;
		if (!r)
			return nfmt;
	}
}

size
c_fmt_fmt(Fmt *p, char *fmt)
{
	usize  nfmt;
	int    n;
	uchar *s;

	s = (uchar *)fmt;
	nfmt = p->nfmt;

	for (; *s; s++) {
		if (*s == '%') {
			if ((n = fmtflag(p, s)) < 0)
				return -1;
			s += n;
			continue;
		}

		if (c_arr_avail(p->mb) <= 1)
			if ((p->fn)(p) < 0)
				return -1;

		c_arr_cat(p->mb, s, sizeof(uchar));
		p->nfmt++;
	}

	return p->nfmt - nfmt;
}
