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

CH32md *c_hsh_crc32p = &md;

static u32int crctab[] = {
	0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9,
	0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
	0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61,
	0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD
};

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
	uchar *s;

	p->b += n;
	s = (uchar *)data;

	for (; n; n--) {
		p->a ^= *s++ << 24;
		p->a  = (p->a << 4) ^ crctab[(p->a >> 28) & 15];
		p->a  = (p->a << 4) ^ crctab[(p->a >> 28) & 15];
	}

	return 0;
}

static int
end(CH32st *p)
{
	for (; p->b; p->b >>= 8) {
		p->a ^=  p->b << 24;
		p->a  = (p->a << 4) ^ crctab[(p->a >> 28) & 15];
		p->a  = (p->a << 4) ^ crctab[(p->a >> 28) & 15];
	}

	p->a ^= 0xFFFFFFFF;

	return 0;
}
