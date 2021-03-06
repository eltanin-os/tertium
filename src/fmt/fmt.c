#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static int
cmp(void *a, void *b)
{
	return (*(char *)a - ((struct fmtverb *)b)->c);
}

static ctype_status
fmtfmt(ctype_fmt *f, uchar *s)
{
	struct fmtverb *p;

	f->r = *s;
	if ((p = c_std_bsearch(s, c_arr_data(&__fmt_Fmts),
	    c_arr_len(&__fmt_Fmts, sizeof(*p)), sizeof(*p), &cmp))) {
		for (; !(p->f);) ;
		return (p->f)(f);
	}
	if ((p = c_std_bsearch(s, __fmt_VFmts, VFMTLEN, sizeof(*p), &cmp))) {
		if (!c_fmt_install(p->c, p->f))
			return (p->f)(f);
	}
	errno = C_EINVAL;
	return -1;
}

static size
fmtflag(ctype_fmt *f, uchar *s)
{
	ctype_status r;
	size nfmt;
	int i;

	f->flags = 0;
	f->width = 0;
	f->prec = 0;
	nfmt = 0;
	for (;;) {
		++nfmt;
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
			while (*s >= '0' && *s <= '9') {
				i = i * 10 + *s - '0';
				++s;
				++nfmt;
			}
			--s;
			--nfmt;
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
c_fmt_fmt(ctype_fmt *p, char *fmt)
{
	size n;
	usize nfmt;
	int ch;
	uchar *s;

	s = (uchar *)fmt;
	nfmt = p->nfmt;
	while (*s) {
		n = 0;
		for (;;) {
			ch = *(s + n);
			if (ch == '%' || ch == '\0')
				break;
			++n;
		}
		__fmt_trycat(p, (char *)s, n);
		s += n;
		if (ch == '%') {
			if ((n = fmtflag(p, s)) < 0)
				return -1;
			s += n + 1;
		}
	}
	return p->nfmt - nfmt;
}
