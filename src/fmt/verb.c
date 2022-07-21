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
	errnum = va_arg(p->args, ctype_error);
	if (errnum == C_ERR_ECSTM) {
		c_std_errstr(buf, sizeof(buf));
	} else {
		c_std_strerror(errnum, buf, sizeof(buf));
	}
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
		if (p->flags & C_FMT_OSHORT) p->flags |= C_FMT_OBYTE;
		p->flags |= C_FMT_OSHORT;
		break;
	case 'l':
		if (p->flags & C_FMT_OLONG) p->flags |= C_FMT_OVLONG;
		p->flags |= C_FMT_OLONG;
		break;
	case 'z':
		p->flags |= C_FMT_OLONG;
		if (sizeof(uintptr) == sizeof(uvlong)) p->flags |= C_FMT_OVLONG;
		break;
	}
	return 1;
}

static ctype_status
Vint(ctype_fmt *p)
{
	uvlong l;
	uint d, u;
	int b, i, n;
	char buf[64];
	char *s;

	if ((b = getbase(p->r)) == 16) p->flags |= C_FMT_OUNSIGNED;
	u = p->flags & C_FMT_OUNSIGNED;

	n = 0;
	if (p->flags & C_FMT_OVLONG) {
		l = va_arg(p->args, uvlong);
		if (!u && (n = (vlong)l < 0)) l = -(vlong)l;
	} else if (p->flags & C_FMT_OLONG) {
		l = va_arg(p->args, ulong);
		if (!u && (n = (long)l < 0)) l = -(long)l;
	} else if (p->flags & C_FMT_OSHORT) {
		l = va_arg(p->args, uint);
		if (!u && (n = (short)l < 0)) l = -(short)l;
	} else if (p->flags & C_FMT_OBYTE) {
		l = va_arg(p->args, uint);
		if (!u && (n = (char)l < 0)) l = -(char)l;
	} else {
		l = va_arg(p->args, uint);
		if (!u && (n = (int)l < 0)) l = -(int)l;
	}

	u = (p->r == 'X') ? 'A' : 'a';
	s = buf + sizeof(buf);
	if (!l) {
		*--s = '0';
	} else {
		i = 0;
		for (; l; ++i) {
			d = l % b;
			if ((p->flags & C_FMT_OCOMMA) && i % 4 == 3) {
				*--s = ',';
				++i;
			}
			*--s = (d < 10) ? d + '0' : u + d - 10;
			l /= b;
		}
	}

	u = (C_FMT_OZERO|C_FMT_OLEFT|C_FMT_OPREC) & ~p->flags;
	if (u == (C_FMT_OLEFT|C_FMT_OPREC)) {
		p->width -= (buf + sizeof(buf)) - s;
		for (; p->width > 0; --p->width) *--s = '0';
		p->width = 0;
	}

	if (p->flags & C_FMT_OSHARP) {
		if (b == 16) {
			*--s = u + 23;
			*--s = '0';
		} else if (b == 8) {
			*--s = '0';
		}
	}

	if (n) {
		*--s = '-';
	} else if (p->flags & C_FMT_OSIGN) {
		*--s = '+';
	} else if (p->flags & C_FMT_OSPACE) {
		*--s = ' ';
	}

	return c_fmt_nput(p, s, (buf + sizeof(buf)) - s);
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
