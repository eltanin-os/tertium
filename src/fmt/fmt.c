#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static int
fmtfmt(CFmt *f, uchar *s)
{
	struct fmtverb *p;
	int i, n;

	n = c_arr_len(&__fmt_Fmts, sizeof(*p));

	for (;;) {
		i = 0;
		f->r = *s;
		for (; i <= n; i++) {
			p = c_arr_get(&__fmt_Fmts, i, sizeof(*p));
			if (p->c == *s) {
				for (; !(p->f);) ;
				return (p->f)(f);
			}
		}

		i = 0;
		for (;;) {
			if (!(p = &__fmt_VFmts[i++]))
				break;
			if (p->c == *s) {
				c_fmt_install(p->c, p->f);
				return (p->f)(f);
			}
		}
	}
}

static int
fmtflag(CFmt *f, uchar *s)
{
	int i, r, nfmt;

	f->flags = 0;
	f->width = 0;
	f->prec = 0;

	nfmt = 0;

	for (;;) {
		nfmt++;
		if (!(f->r = *++s))
			return -1;

		switch (f->r) {
		case '.':
			f->flags = C_FMTWIDTH | C_FMTPREC;
			continue;
		case '0':
			if (!(f->flags & C_FMTWIDTH)) {
				f->flags |= C_FMTZERO;
				continue;
			}
			/* FALLTHROUGH */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			i = 0;
			for (; *s >= '0' && *s <= '9'; nfmt++, s++)
				i = i * 10 + *s - '0';
			s--;
			nfmt--;
numflag:
			if (f->flags & C_FMTWIDTH) {
				f->flags |= C_FMTPREC;
				f->prec = i;
			} else {
				f->flags |= C_FMTWIDTH;
				f->width = i;
			}
			continue;
		case '*':
			if ((i = va_arg(f->args, int)) < 0) {
				if (f->flags & C_FMTPREC) {
					f->flags &= ~C_FMTPREC;
					f->prec = 0;
					continue;
				}
				i = -i;
				f->flags |= C_FMTLEFT;
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
c_fmt_fmt(CFmt *p, char *fmt)
{
	usize nfmt;
	int n;
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

		__fmt_trycat(p, (char *)s, 1, sizeof(uchar));
	}

	return p->nfmt - nfmt;
}
