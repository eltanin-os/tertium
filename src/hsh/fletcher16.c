#include <tertium/cpu.h>
#include <tertium/std.h>

static int init(CH32st *);
static int update(CH32st *, char *, usize);
static int end(CH32st *);

static CH32md md = {
	&init,
	&update,
	&end,
};

CH32md * c_hsh_fletcher16 = &md;

static int
init(CH32st *p)
{
	p->a = 0;
	p->b = 0;
	return 0;
}

static int
update(CH32st *p, char *data, usize n)
{
	u16int *s;

	s = (u16int *)data;
	n /= 2;

	for (; n; n--, s++)
		p->b += p->a += (*s & 0xFFFF) + (*s >> 16);

	return 0;
}

static int
end(CH32st *p)
{
	p->a = (p->b << 16) | p->a;
	return 0;
}
