#include <tertium/cpu.h>
#include <tertium/std.h>

#include "verb.h"

#define getbase(a) \
((a)=='p'||(a)=='x'||(a)=='X')?16:((a)=='o')?8:((a)=='b')?2:10;

static int __Vchar(CFmt *);
static int __Verr(CFmt *);
static int __Vflag(CFmt *);
static int __Vint(CFmt *);
static int __Vperc(CFmt *);
static int __Vstr(CFmt *);

static uchar buf[64*sizeof(struct fmtverb)];
CArr Fmts = c_arr_INIT(buf);

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
trycat(CFmt *p, char *s, usize m, usize n)
{
	usize t, w;

	if (C_OFLW_UM(usize, n, m))
		return -1;

	t = m*n;

	for (;;) {
		if (t > c_arr_avail(p->mb))
			if ((p->fn)(p) < 0)
				return -1;
		w = C_MIN(t, c_arr_avail(p->mb));
		c_arr_cat(p->mb, s, w);
		t       -= w;
		s       += w;
		p->nfmt += w;
		if (!t)
			return 0;
	}
}

static int
fmtpad(CFmt *p, usize n)
{
	int w;
	w = p->width - n;
	for (; w > 0; w--)
		if (trycat(p, " ", 1, sizeof(uchar)) < 0)
			return -1;
	return 0;
}

static int
fmtcat(CFmt *p, char *s, usize n)
{
	if (!s)
		s = "<nil>";
	if (!n)
		n = (char *)c_mem_chr(s, C_USIZEMAX, 0)-s;
	if ((p->flags & C_FMTPREC) && n > p->prec)
		n = p->prec;
	if (!(p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;
	if (trycat(p, s, n, sizeof(uchar)) < 0)
		return -1;
	if ((p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;
	return 0;
}

static int
__Vchar(CFmt *p)
{
	char buf[8];
	int x;
	x = va_arg(p->args, int);
	c_mem_cpy(buf, sizeof(x), &x);
	buf[sizeof(x)] = '\0';
	return fmtcat(p, buf, 0);
}

static int
__Verr(CFmt *p)
{
	char buf[C_ERRSIZ];
	c_sys_errstr(buf, sizeof(buf));
	return fmtcat(p, buf, 0);
}

static int
__Vflag(CFmt *p)
{
	switch(p->r){
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
		if(p->flags & C_FMTSHORT)
			p->flags |= C_FMTBYTE;
		p->flags |= C_FMTSHORT;
		break;
	case 'l':
		if(p->flags & C_FMTLONG)
			p->flags |= C_FMTVLONG;
		p->flags |= C_FMTLONG;
		break;
	case 'z':
		p->flags |= C_FMTLONG;
		if(sizeof(uintptr) == sizeof(uvlong))
			p->flags |= C_FMTVLONG;
		break;
	}
	return 1;
}

static int
__Vint(CFmt *p)
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
	for (; l; j++) {
		d = (l % b);
		if ((p->flags & C_FMTCOMMA) && j % 4 == 3) {
			buf[--i] = ',';
			j++;
		}
		buf[--i] = (d < 10) ? d + '0' : u + d - 10;
		l /= b;
	}
	if ((p->flags & C_FMTZERO) && !(p->flags & (C_FMTLEFT|C_FMTPREC))) {
		p->width -= sizeof(buf)-i;
		for (; p->width > 0; p->width--)
			buf[--i] = '0';
		p->width = 0;
	}
	if (p->flags & C_FMTSHARP) {
		if (b == 16)
			buf[--i] = u+23; /* 'x' */
		if (b == 16 || b == 8)
			buf[--i] = '0';
	}
	if (n)
		buf[--i] = '-';
	else if (p->flags & C_FMTSIGN)
		buf[--i] = '+';
	else if (p->flags & C_FMTSPACE)
		buf[--i] = ' ';
	return fmtcat(p, buf+i, sizeof(buf)-i);
}

static int
__Vperc(CFmt *p)
{
	p->prec = 1;
	return fmtcat(p, "%", 1);;
}

static int
__Vstr(CFmt *p)
{
	char *s;
	s = va_arg(p->args, char *);
	return fmtcat(p, s, 0);
}
