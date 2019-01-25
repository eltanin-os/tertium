#include <tertium/cpu.h>
#include <tertium/std.h>

static int init(CH32st *);
static int update(CH32st *, char *, usize);
static int end(CH32st *);

CH32md md = {
	&init,
	&update,
	&end,
};

CH32md *c_hsh_edf = &md;

static int
init(CH32st *p)
{
	p->a = 0;
	return 0;
}

static int
update(CH32st *p, char *data, usize n)
{
	uchar *s;

	s = (uchar *)data;

	for (; n; n--)
		p->a = (p->a * 4327) + *s++;

	return 0;
}

static int
end(CH32st *p)
{
	p->a += p->a << 24;
	p->a ^= p->a >> 5;
	p->a += p->a << 3;
	p->a ^= p->a >> 17;
	p->a += p->a << 7;
	return 0;
}
