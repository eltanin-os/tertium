#include <tertium/cpu.h>
#include <tertium/std.h>

#define C1 0xCC9E2D51
#define C2 0x1B873593

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
};

ctype_hmd *c_hsh_murmur32 = &md;

static void
init(ctype_hst *p)
{
	p->curlen = 0;
	p->len = 0;
	p->st.x32[0] = 0xDEAFB0FAU;
}

static void
compress(ctype_hst *p, char *data)
{
	u32 k;
	/* key */
	k = c_uint_32unpack(data);
	k *= C1;
	k = c_hsh_rol32(k, 15);
	k *= C2;
	/* hash */
	p->st.x32[0] ^= k;
	p->st.x32[0] = c_hsh_rol32(p->st.x32[0], 13);
	p->st.x32[0] = p->st.x32[0] * 5 + 0xE6546B64;
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 4, p, data, n);
}

static void
end(ctype_hst *p, char *s)
{
	u32 k;

	k = 0;
	switch (p->curlen) {
	case 3:
		k ^= p->buf[2] << 16;
		/* FALLTHROUGH */
	case 2:
		k ^= p->buf[1] << 8;
		/* FALLTHROUGH */
	case 1:
		k ^= p->buf[0];
		k *= C1;
		k = c_hsh_rol32(k, 15);
		k *= C2;
	}
	p->st.x32[0] ^= k;
	p->len += p->curlen << 3;
	p->st.x32[0] ^= c_hsh_octets(p);
	/* mix */
	p->st.x32[0] ^= p->st.x32[0] >> 16;
	p->st.x32[0] *= 0x85EBCA6B;
	p->st.x32[0] ^= p->st.x32[0] >> 13;
	p->st.x32[0] *= 0xC2B2AE35;
	p->st.x32[0] ^= p->st.x32[0] >> 16;
	/* digest */
	c_uint_32pack(s, p->st.x32[0]);
}
