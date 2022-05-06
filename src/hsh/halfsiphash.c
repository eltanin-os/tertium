#include <tertium/cpu.h>
#include <tertium/std.h>

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
};

ctype_hmd *c_hsh_halfsiphash = &md;

static void
sipround(ctype_hst *p)
{
	p->st.x32[0] += p->st.x32[1];
	p->st.x32[1] = c_hsh_rol32(p->st.x32[1], 5);
	p->st.x32[1] ^= p->st.x32[0];
	p->st.x32[0] = c_hsh_rol32(p->st.x32[0], 16);
	p->st.x32[2] += p->st.x32[3];
	p->st.x32[3] = c_hsh_rol32(p->st.x32[3], 8);
	p->st.x32[3] ^= p->st.x32[2];
	p->st.x32[0] += p->st.x32[3];
	p->st.x32[3] = c_hsh_rol32(p->st.x32[3], 7);
	p->st.x32[3] ^= p->st.x32[0];
	p->st.x32[2] += p->st.x32[1];
	p->st.x32[1] = c_hsh_rol32(p->st.x32[1], 13);
	p->st.x32[1] ^= p->st.x32[2];
	p->st.x32[2] = c_hsh_rol32(p->st.x32[2], 16);
}

static void
sipround2(ctype_hst *p)
{
	sipround(p);
	sipround(p);
}

static void
sipround4(ctype_hst *p)
{
	sipround2(p);
	sipround2(p);
}

static void
init(ctype_hst *p)
{
	u32 k0, k1;
	/* length */
	p->curlen = 0;
	p->len = 0;
	/* key seed */
	k0 = c_uint_32unpack((char *)p->buf);
	k1 = c_uint_32unpack((char *)(p->buf + 4));
	/* v[0-3] */
	p->st.x32[0] = k0 ^ 0;
	p->st.x32[1] = k1 ^ 0;
	p->st.x32[2] = k0 ^ 0x6c796765;
	p->st.x32[3] = k1 ^ 0x74656462;
}

static void
compress(ctype_hst *p, char *data)
{
	u32 x;
	x = c_uint_32unpack(data);
	p->st.x32[3] ^= x;
	sipround2(p); /* cround */
	p->st.x32[0] ^= x;
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 4, p, data, n);
}

static void
end(ctype_hst *p, char *s)
{
	u32 r;

	p->len += p->curlen << 3;
	r = c_hsh_octets(p) << 24;

	switch (p->curlen) {
	case 3:
		r |= (u64)p->buf[2] << 16;
		/* FALLTHROUGH */
	case 2:
		r |= (u64)p->buf[1] << 8;
		/* FALLTHROUGH */
	case 1:
		r |= (u64)p->buf[0];
	}

	p->st.x32[3] ^= r;
	sipround2(p); /* cround */
	p->st.x32[0] ^= r;
	p->st.x32[2] ^= 0xff;
	sipround4(p); /* dround */

	r = p->st.x64[1] ^  p->st.x64[3];
	c_uint_64pack(s, r);
}
