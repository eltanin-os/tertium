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

CH32md *c_hsh_djb = &md;

static void
init(CH32st *p)
{
	p->len = 0;
	p->state[0] = 5381;
}

static void
update(CH32st *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->state[0] = (p->state[0] + (p->state[0] << 5)) ^ *s++;
}

static void
end(CH32st *p)
{
	(void)p;
}
