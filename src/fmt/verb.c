#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define getbase(a) \
((a) == 'p' || (a | 32) == 'x' ? 16 : ((a) == 'o') ? 8 : ((a) == 'b') ? 2 : 10)

static ctype_status Vchar(ctype_fmt *);
static ctype_status Verr(ctype_fmt *);
static ctype_status Vflag(ctype_fmt *);
static ctype_status Vint(ctype_fmt *);
static ctype_status Vperc(ctype_fmt *);
static ctype_status Vstr(ctype_fmt *);

static uchar buf[64 * sizeof(struct fmtverb)];
ctype_arr __fmt_Fmts = c_arr_INIT(buf);

struct fmtverb __fmt_VFmts[] = {
	{ ',', Vflag },
	{ '-', Vflag },
	{ '+', Vflag },
	{ '#', Vflag },
	{ '%', Vperc },
	{ ' ', Vflag },
	{ 'X', Vint  },
	{ 'b', Vint  },
	{ 'c', Vchar },
	{ 'd', Vint  },
	{ 'h', Vflag },
	{ 'l', Vflag },
	{ 'o', Vint  },
	{ 'p', Vint  },
	{ 'u', Vflag },
	{ 'r', Verr  },
	{ 's', Vstr  },
	{ 'x', Vint  },
	{ 'z', Vflag },
	{   0, nil   },
};

ctype_status
__fmt_trycat(ctype_fmt *p, char *s, usize n)
{
	size r;

	if ((r = p->func(p, s, n)) < 0)
		return -1;

	p->nfmt += r;
	return 0;
}

static ctype_status
fmtpad(ctype_fmt *p, usize n)
{
	int w;

	w = p->width - n;

	for (; w > 0; w--)
		if (__fmt_trycat(p, " ", 1) < 0)
			return -1;

	return 0;
}

static ctype_status
fmtcat(ctype_fmt *p, char *s, usize n)
{
	if (!s)
		s = "<nil>";

	if (!n)
		n = c_str_len(s, C_USIZEMAX);

	if ((p->flags & C_FMTPREC) && n > (usize)p->prec)
		n = p->prec;

	if ((p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;

	if (__fmt_trycat(p, s, n) < 0)
		return -1;

	if (!(p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;

	return 0;
}

static ctype_status
Vchar(ctype_fmt *p)
{
	char buf[8];
	int x;

	x = va_arg(p->args, int);
	c_mem_cpy(buf, sizeof(x), &x);
	buf[sizeof(x) - 1] = 0;
	return fmtcat(p, buf, sizeof(x));
}

static ctype_status
Verr(ctype_fmt *p)
{
	char buf[C_ERRSIZ];

	if (errno == C_ECSTM)
		c_sys_errstr(buf, sizeof(buf));
	else
		c_sys_strerror(errno, buf, sizeof(buf));

	return fmtcat(p, buf, 0);
}

static ctype_status
Vflag(ctype_fmt *p)
{
	switch (p->r) {
	case ',':
		p->flags |= C_FMTCOMMA;
		break;
	case '-':
		p->flags |= C_FMTLEFT;
		break;
	case '+':
		p->flags |= C_FMTSIGN;
		break;
	case '#':
		p->flags |= C_FMTSHARP;
		break;
	case ' ':
		p->flags |= C_FMTSPACE;
		break;
	case 'u':
		p->flags |= C_FMTUNSIGNED;
		break;
	case 'h':
		if (p->flags & C_FMTSHORT)
			p->flags |= C_FMTBYTE;
		p->flags |= C_FMTSHORT;
		break;
	case 'l':
		if (p->flags & C_FMTLONG)
			p->flags |= C_FMTVLONG;
		p->flags |= C_FMTLONG;
		break;
	case 'z':
		p->flags |= C_FMTLONG;
		if (sizeof(uintptr) == sizeof(uvlong))
			p->flags |= C_FMTVLONG;
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

	if (!(p->flags & C_FMTUNSIGNED) && (vlong)l < 0) {
		n++;
		l = -(vlong)l;
	}

	b = getbase(p->r);
	u = (p->r == 'X') ? 'A' : 'a';
	i = sizeof(buf) - 1;
	j = 0;

	if (!l)
		buf[--i] = '0';

	for (; l; j++) {
		d = (l % b);
		if ((p->flags & C_FMTCOMMA) && j % 4 == 3) {
			buf[--i] = ',';
			j++;
		}
		buf[--i] = (d < 10) ? d + '0' : u + d - 10;
		l /= b;
	}

	if ((p->flags & C_FMTZERO) && !(p->flags & (C_FMTLEFT | C_FMTPREC))) {
		p->width -= sizeof(buf) - i;
		for (; p->width >= 0; --p->width)
			buf[--i] = '0';
		p->width = 0;
	}

	if (p->flags & C_FMTSHARP) {
		if (b == 16)
			buf[--i] = u + 23;	/* 'x' */
		if (b == 16 || b == 8)
			buf[--i] = '0';
	}

	if (n)
		buf[--i] = '-';
	else if (p->flags & C_FMTSIGN)
		buf[--i] = '+';
	else if (p->flags & C_FMTSPACE)
		buf[--i] = ' ';

	return fmtcat(p, buf + i, sizeof(buf) - (i + 1));
}

static ctype_status
Vperc(ctype_fmt *p)
{
	p->prec = 1;
	return fmtcat(p, "%", 1);;
}

static ctype_status
Vstr(ctype_fmt *p)
{
	char *s;

	s = va_arg(p->args, char *);
	return fmtcat(p, s, 0);
}
