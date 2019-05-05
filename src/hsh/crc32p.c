#include <tertium/cpu.h>
#include <tertium/std.h>

#define CRCTAB(a) \
(((a) << 4) ^ crctab[((a) >> 28) & 15])

static void init(CH32st *);
static void update(CH32st *, char *, usize);
static void end(CH32st *);

static CH32md md = {
	&init,
	&update,
	&end,
};

CH32md *c_hsh_crc32p = &md;

static u32int crctab[] = {
	0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9,
	0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
	0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61,
	0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD
};

static void
init(CH32st *p)
{
	p->len = 0;
	p->state[0] = 0;
}

static void
update(CH32st *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--) {
		p->state[0] ^= *s++ << 24;
		p->state[0]  = CRCTAB(p->state[0]);
		p->state[0]  = CRCTAB(p->state[0]);
	}
}

static void
end(CH32st *p)
{
	usize n;
	for (n = p->len; n; n >>= 8) {
		p->state[0] ^= n << 24;
		p->state[0]  = CRCTAB(p->state[0]);
		p->state[0]  = CRCTAB(p->state[0]);
	}
	p->state[0] ^= 0xFFFFFFFF;
}
