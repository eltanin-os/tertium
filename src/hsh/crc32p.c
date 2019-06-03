#include <tertium/cpu.h>
#include <tertium/std.h>

#define CRCTAB(a) \
(((a) << 4) ^ crctab[((a) >> 28) & 15])

static void init(CHst *);
static void update(CHst *, char *, usize);
static void end(CHst *);

static CHmd md = {
	&init,
	&update,
	&end,
	nil,
};

CHmd *c_hsh_crc32p = &md;

static u32int crctab[] = {
	0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9,
	0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
	0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61,
	0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD
};

static void
init(CHst *p)
{
	p->len = 0;
	p->st.x32[0] = 0;
}

static void
update(CHst *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--) {
		p->st.x32[0] ^= *s++ << 24;
		p->st.x32[0]  = CRCTAB(p->st.x32[0]);
		p->st.x32[0]  = CRCTAB(p->st.x32[0]);
	}
}

static void
end(CHst *p)
{
	usize n;
	for (n = p->len; n; n >>= 8) {
		p->st.x32[0] ^= n << 24;
		p->st.x32[0]  = CRCTAB(p->st.x32[0]);
		p->st.x32[0]  = CRCTAB(p->st.x32[0]);
	}
	p->st.x32[0] ^= 0xFFFFFFFF;
}
