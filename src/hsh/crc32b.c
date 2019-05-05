#include <tertium/cpu.h>
#include <tertium/std.h>

#define CRCTAB(a) \
(((a) >> 4) ^ crctab[(a) & 15])

static void init(CH32st *);
static void update(CH32st *, char *, usize);
static void end(CH32st *);

static CH32md md = {
	&init,
	&update,
	&end,
};

CH32md *c_hsh_crc32b = &md;

static u32int crctab[] = {
	0x00000000, 0x1DB71064, 0x3B6E20C8, 0x26D930AC,
	0x76DC4190, 0x6B6B51F4, 0x4DB26158, 0x5005713C,
	0xEDB88320, 0xF00F9344, 0xD6D6A3E8, 0xCB61B38C,
	0x9B64C2B0, 0x86D3D2D4, 0xA00AE278, 0xBDBDF21C
};

static void
init(CH32st *p)
{
	p->len = 0;
	p->state[0] = 0xFFFFFFFF;
}

static void
update(CH32st *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--) {
		p->state[0] ^= *s++;
		p->state[0]  = CRCTAB(p->state[0]);
		p->state[0]  = CRCTAB(p->state[0]);
	}
}

static void
end(CH32st *p)
{
	p->state[0] ^= 0xFFFFFFFF;
}
