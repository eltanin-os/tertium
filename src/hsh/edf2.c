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

CH32md *c_hsh_edf2 = &md;

static void
init(CH32st *p)
{
	p->len = 0;
	p->state[0] = 9311;
}

static void
update(CH32st *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->state[0] = (p->state[0] + (*s++ - ' ')) * 1237;
}

static void
end(CH32st *p)
{
	p->state[0] += p->state[0] << 13;
	p->state[0] ^= p->state[0] >> 7;
	p->state[0] += p->state[0] << 15;
	p->state[0] ^= p->state[0] >> 5;
	p->state[0] += p->state[0] << 3;
}
