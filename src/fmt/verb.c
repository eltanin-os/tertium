#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

#define getbase(a) \
((a) == 'p' || (a | 32) == 'x' ? 16 : ((a) == 'o') ? 8 : ((a) == 'b') ? 2 : 10)

static ctype_status Vchar(ctype_fmt *);
static ctype_status Verr(ctype_fmt *);
static ctype_status Vflag(ctype_fmt *);
static ctype_status Vint(ctype_fmt *);
static ctype_status Vperc(ctype_fmt *);
static ctype_status Vstr(ctype_fmt *);

ctype_arr _tertium_fmt_fmts;

struct fmtverb _tertium_fmt_vfmts[] = {
	{ ' ', Vflag },
	{ '#', Vflag },
	{ '%', Vperc },
	{ '+', Vflag },
	{ ',', Vflag },
	{ '-', Vflag },
	{ 'X', Vint  },
	{ 'b', Vint  },
	{ 'c', Vchar },
	{ 'd', Vint  },
	{ 'h', Vflag },
	{ 'l', Vflag },
	{ 'o', Vint  },
	{ 'p', Vint  },
	{ 'r', Verr  },
	{ 's', Vstr  },
	{ 'u', Vflag },
	{ 'x', Vint  },
	{ 'z', Vflag },
};

static ctype_status
Vchar(ctype_fmt *p)
{
	ctype_rune r;
	char buf[8];

	r = va_arg(p->args, ctype_rune);
	c_mem_cpy(buf, sizeof(r), &r);
	return c_fmt_nput(p, buf, c_utf8_chartorune(&r, buf));
}

static ctype_status
Verr(ctype_fmt *p)
{
	ctype_error errnum;
	char buf[C_IOQ_ERRSIZ];

	if ((errnum = va_arg(p->args, ctype_error)) == C_ERR_ECSTM)
		c_std_errstr(buf, sizeof(buf));
	else
		c_std_strerror(errnum, buf, sizeof(buf));

	return c_fmt_put(p, buf);
}

static ctype_status
Vflag(ctype_fmt *p)
{
	switch (p->r) {
	case ',':
		p->flags |= C_FMT_OCOMMA;
		break;
	case '-':
		p->flags |= C_FMT_OLEFT;
		break;
	case '+':
		p->flags |= C_FMT_OSIGN;
		break;
	case '#':
		p->flags |= C_FMT_OSHARP;
		break;
	case ' ':
		p->flags |= C_FMT_OSPACE;
		break;
	case 'u':
		p->flags |= C_FMT_OUNSIGNED;
		break;
	case 'h':
		if (p->flags & C_FMT_OSHORT)
			p->flags |= C_FMT_OBYTE;
		p->flags |= C_FMT_OSHORT;
		break;
	case 'l':
		if (p->flags & C_FMT_OLONG)
			p->flags |= C_FMT_OVLONG;
		p->flags |= C_FMT_OLONG;
		break;
	case 'z':
		p->flags |= C_FMT_OLONG;
		if (sizeof(uintptr) == sizeof(uvlong))
			p->flags |= C_FMT_OVLONG;
		break;
	}
	return 1;
}

static ctype_status
Vint(ctype_fmt *p)
{
	uvlong l;
	int b, d, i, j, u, n;
	char buf[64];

	n = 0;
	l = va_arg(p->args, uvlong);

	if (!(p->flags & C_FMT_OUNSIGNED) && (vlong)l < 0) {
		++n;
		l = -(vlong)l;
	}

	b = getbase(p->r);
	u = (p->r == 'X') ? 'A' : 'a';
	i = sizeof(buf) - 1;
	j = 0;

	if (!l)
		buf[--i] = '0';

	for (; l; ++j) {
		d = (l % b);
		if ((p->flags & C_FMT_OCOMMA) && j % 4 == 3) {
			buf[--i] = ',';
			++j;
		}
		buf[--i] = (d < 10) ? d + '0' : u + d - 10;
		l /= b;
	}

	if ((p->flags & C_FMT_OZERO) &&
	    !(p->flags & (C_FMT_OLEFT | C_FMT_OPREC))) {
		p->width -= sizeof(buf) - i;
		for (; p->width >= 0; --p->width)
			buf[--i] = '0';
		p->width = 0;
	}

	if (p->flags & C_FMT_OSHARP) {
		if (b == 16)
			buf[--i] = u + 23;	/* 'x' */
		if (b == 16 || b == 8)
			buf[--i] = '0';
	}

	if (n)
		buf[--i] = '-';
	else if (p->flags & C_FMT_OSIGN)
		buf[--i] = '+';
	else if (p->flags & C_FMT_OSPACE)
		buf[--i] = ' ';

	return c_fmt_nput(p, buf + i, sizeof(buf) - (i + 1));
}

static ctype_status
Vperc(ctype_fmt *p)
{
	p->prec = 1;
	return c_fmt_nput(p, "%", 1);;
}

static ctype_status
Vstr(ctype_fmt *p)
{
	char *s;
	s = va_arg(p->args, char *);
	return c_fmt_put(p, s);
}
