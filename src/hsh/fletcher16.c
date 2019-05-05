#include <tertium/cpu.h>
#include <tertium/std.h>

static void init(CH32st *);
static void update(CH32st *, char *, usize);
static void end(CH32st *);

static CH32md md = {
	&init,
	&update,
	&end,
};

CH32md * c_hsh_fletcher16 = &md;

static void
init(CH32st *p)
{
	p->state[0] = p->state[1] = 0;
}

static void
update(CH32st *p, char *data, usize n)
{
	u16int *s;

	p->len += n;
	n /= 2;
	s  = (u16int *)data;

	for (; n; n--, s++)
		p->state[1] += p->state[0] += (*s & 0xFFFF) + (*s >> 16);
}

static void
end(CH32st *p)
{
	p->state[0] = (p->state[1] << 16) | p->state[0];
}
