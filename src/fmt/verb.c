#include <tertium/cpu.h>
#include <tertium/std.h>

#include "verb.h"

#define getbase(a) \
((a)=='p'||(a)=='x'||(a)=='X')?16:((a)=='o')?8:((a)=='b')?2:10;

static int __Vchar(Fmt *);
static int __Verr(Fmt *);
static int __Vflag(Fmt *);
static int __Vint(Fmt *);
static int __Vperc(Fmt *);
static int __Vstr(Fmt *);

static uchar buf[64*sizeof(struct fmtverb)];
Membuf Fmts = c_arr_INIT(buf);

struct fmtverb VFmts[] = {
	{ ',', __Vflag },
	{ '-', __Vflag },
	{ '+', __Vflag },
	{ '#', __Vflag },
	{ '%', __Vperc },
	{ ' ', __Vflag },
	{ 'X', __Vint  },
	{ 'b', __Vint  },
	{ 'c', __Vchar },
	{ 'd', __Vint  },
	{ 'h', __Vflag },
	{ 'l', __Vflag },
	{ 'o', __Vint  },
	{ 'p', __Vint  },
	{ 'u', __Vflag },
	{ 'r', __Verr  },
	{ 's', __Vstr  },
	{ 'x', __Vint  },
	{ 'z', __Vflag },
	{   0, nil     },
};

static int
trycat(Fmt *p, char *s, usize m, usize n)
{
	usize t, w;

	if (n && m > (usize)-1/n)
		return -1;

	t = m*n;
	w = 0;

	for (;;) {
		if (t > c_arr_avail(p->mb))
			if ((p->fn)(p) < 0)
				return -1;

		w = 0;
		if (t > c_arr_avail(p->mb))
			w = t - c_arr_avail(p->mb);

		t -= w;
		c_arr_cat(p->mb, s, t, sizeof(uchar));
		s += t;
		if (!(t = w))
			return 0;
	}
}

static int
fmtpad(Fmt *p, usize n)
{
	int w;
	w = p->width - n;
	for (; w > 0; w--)
		if (trycat(p, " ", 1, sizeof(uchar)) < 0)
			return -1;
	p->width = 0;
	return 0;
}

static int
fmtcat(Fmt *p, char *s, usize n)
{
	if (!s)
		s = "<nil>";
	if (!n)
		n = (char *)c_mem_chr(s, USIZE_MAX, 0)-s;
	if (!(p->flags & FmtLeft) && fmtpad(p, n) < 0)
		return -1;
	if ((p->flags & FmtPrec) && n > p->prec)
		n = p->prec;
	if (trycat(p, s, n, sizeof(uchar)) < 0)
		return -1;
	if ((p->flags & FmtLeft) && fmtpad(p, n) < 0)
		return -1;
	return 0;
}

static int
__Vchar(Fmt *p)
{
	char buf[8];
	int x;
	x = va_arg(p->args, int);
	c_mem_cpy(buf, sizeof(x), &x);
	buf[sizeof(x)] = '\0';
	return fmtcat(p, buf, 0);
}

static int
__Verr(Fmt *p)
{
	char buf[ERRBUFSIZ];
	c_sys_errstr(buf, sizeof(buf));
	return fmtcat(p, buf, 0);
}

static int
__Vflag(Fmt *p)
{
	switch(p->r){
	case ',':
		p->flags |= FmtComma;
		break;
	case '-':
		p->flags |= FmtLeft;
		break;
	case '+':
		p->flags |= FmtSign;
		break;
	case '#':
		p->flags |= FmtSharp;
		break;
	case ' ':
		p->flags |= FmtSpace;
		break;
	case 'u':
		p->flags |= FmtUnsigned;
		break;
	case 'h':
		if(p->flags & FmtShort)
			p->flags |= FmtByte;
		p->flags |= FmtShort;
		break;
	case 'l':
		if(p->flags & FmtLong)
			p->flags |= FmtVLong;
		p->flags |= FmtLong;
		break;
	case 'z':
		p->flags |= FmtLong;
		if(sizeof(uintptr) == sizeof(uvlong))
			p->flags |= FmtVLong;
		break;
	}
	return 1;
}

static int
__Vint(Fmt *p)
{
	uvlong l;
	int b, d, i, j, u, n;
	char buf[64];
	n = 0;
	if ((vlong)(l = va_arg(p->args, vlong)) < 0) {
		n++;
		l = -l;
	}
	b = getbase(p->r);
	u = (p->r == 'X') ? 'A' : 'a';
	i = sizeof(buf)-1;
	j = 0;
	if (!l) buf[i] = '0';
	for (; l; i--, j++) {
		d = (l % b);
		if ((p->flags & FmtComma) && j % 4 == 3) {
			buf[i--] = ',';
			j++;
		}
		buf[i] = (d < 10) ? d + '0' : u + d - 10;
		l /= b;
	}
	if ((p->flags & FmtZero) && !(p->flags & (FmtLeft|FmtPrec))) {
		p->width -= sizeof(buf)-i;
		for (; p->width > 0; p->width--)
			buf[--i] = '0';
		p->width = 0;
	}
	if (p->flags & FmtSharp) {
		if (b == 16)
			buf[--i] = u+23; /* 'x' */
		if (b == 16 || b == 8)
			buf[--i] = '0';
	}
	if (n)
		buf[--i] = '-';
	else if (p->flags & FmtSign)
		buf[--i] = '+';
	else if (p->flags & FmtSpace)
		buf[--i] = ' ';
	return fmtcat(p, buf+i, sizeof(buf)-i);
}

static int
__Vperc(Fmt *p)
{
	p->prec = 1;
	return fmtcat(p, "%", 1);;
}

static int
__Vstr(Fmt *p)
{
	char *s;
	s = va_arg(p->args, char *);
	return fmtcat(p, s, 0);
}
