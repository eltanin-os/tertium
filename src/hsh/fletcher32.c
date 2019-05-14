#include <tertium/cpu.h>
#include <tertium/std.h>

#define SUM16(a, b, c, d) \
do { a += b += c_uint_16unpack((char *)d); \
     c -= 2; d += 2; } while (c >= 2)

static void init(CH32st *);
static void update(CH32st *, char *, usize);
static void end(CH32st *);

static CH32md md = {
	&init,
	&update,
	&end,
};

CH32md * c_hsh_fletcher32 = &md;

static void
init(CH32st *p)
{
	p->state[0] = p->state[1] = 0;
}

static void
update(CH32st *p, char *data, usize n)
{
	usize i;

	p->len += n;
	i = 0;

	while (n >= 2) {
		n -= i = C_MIN(360, n);
		SUM16(p->state[1], p->state[0], i, data);
		p->state[0] = (p->state[0] & 0xFFFF) + (p->state[0] >> 16);
		p->state[1] = (p->state[1] & 0xFFFF) + (p->state[1] >> 16);
	}

	if (n) {
		p->state[1] += p->state[0] += (uchar)data[0];
		p->state[0]  = (p->state[0] & 0xFFFF) + (p->state[0] >> 16);
		p->state[1]  = (p->state[1] & 0xFFFF) + (p->state[1] >> 16);
	}
}

static void
end(CH32st *p)
{
	p->state[0] = (p->state[1] << 16) | p->state[0];
}
