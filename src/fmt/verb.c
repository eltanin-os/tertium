#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define getbase(a) \
((a)=='p'||(a)=='x'||(a)=='X')?16:((a)=='o')?8:((a)=='b')?2:10;

static int Vchar(CFmt *);
static int Verr(CFmt *);
static int Vflag(CFmt *);
static int Vint(CFmt *);
static int Vperc(CFmt *);
static int Vstr(CFmt *);

static uchar buf[64*sizeof(struct fmtverb)];
CArr __fmt_Fmts = c_arr_INIT(buf);

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

static size
nobuffer(CFmt *p, char *s, usize n)
{
	return c_sys_allrw(p->op, (uintptr)p->farg, s, C_MIN(n, C_BIOSIZ));
}

static size
buffered(CFmt *p, char *s, usize n)
{
	size r;

	if (n > c_arr_avail(p->mb) && p->fn(p) < 0)
		return -1;

	c_arr_cat(p->mb, s, (r = C_MIN(n, c_arr_avail(p->mb))), sizeof(uchar));

	return r;
}

int
__fmt_trycat(CFmt *p, char *s, usize m, usize n)
{
	size (*f)(CFmt *, char *, usize);
	size r;

	if (C_OFLW_UM(usize, n, m))
		return -1;

	m *= n;

	f = p->mb->a ? buffered : nobuffer;
	while (m) {
		if ((r = f(p, s, m)) < 0)
			return -1;
		m -= r;
		s += r;
		p->nfmt += r;
	}

	return 0;
}

static int
fmtpad(CFmt *p, usize n)
{
	int w;
	w = p->width - n;
	for (; w > 0; w--)
		if (__fmt_trycat(p, " ", 1, sizeof(uchar)) < 0)
			return -1;
	return 0;
}

static int
fmtcat(CFmt *p, char *s, usize n)
{
	if (!s)
		s = "<nil>";
	if (!n)
		n = c_str_len(s, C_USIZEMAX);
	if ((p->flags & C_FMTPREC) && n > (usize)p->prec)
		n = p->prec;
	if (!(p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;
	if (__fmt_trycat(p, s, n, sizeof(uchar)) < 0)
		return -1;
	if ((p->flags & C_FMTLEFT) && fmtpad(p, n) < 0)
		return -1;
	return 0;
}

static int
Vchar(CFmt *p)
{
	char buf[8];
	int x;
	x = va_arg(p->args, int);
	c_mem_cpy(buf, sizeof(x), &x);
	buf[sizeof(x)] = '\0';
	return fmtcat(p, buf, 0);
}

static int
Verr(CFmt *p)
{
	char buf[C_ERRSIZ];

	if (errno == C_ECSTM)
		c_sys_errstr(buf, sizeof(buf));
	else
		c_sys_strerror(errno, buf, sizeof(buf));

	return fmtcat(p, buf, 0);
}

static int
Vflag(CFmt *p)
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
Vint(CFmt *p)
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
	i = sizeof(buf)-1;
	j = 0;
	if (!l) buf[--i] = '0';
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
	return fmtcat(p, buf+i, sizeof(buf)-(i+1));
}

static int
Vperc(CFmt *p)
{
	p->prec = 1;
	return fmtcat(p, "%", 1);;
}

static int
Vstr(CFmt *p)
{
	char *s;
	s = va_arg(p->args, char *);
	return fmtcat(p, s, 0);
}
