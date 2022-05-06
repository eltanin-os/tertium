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

ctype_hmd *c_hsh_siphash = &md;

static void
sipround(ctype_hst *p)
{
	p->st.x64[0] += p->st.x64[1];
	p->st.x64[1] = c_hsh_rol64(p->st.x64[1], 13);
	p->st.x64[1] ^= p->st.x64[0];
	p->st.x64[0] = c_hsh_rol64(p->st.x64[0], 32);
	p->st.x64[2] += p->st.x64[3];
	p->st.x64[3] = c_hsh_rol64(p->st.x64[3], 16);
	p->st.x64[3] ^= p->st.x64[2];
	p->st.x64[0] += p->st.x64[3];
	p->st.x64[3] = c_hsh_rol64(p->st.x64[3], 21);
	p->st.x64[3] ^= p->st.x64[0];
	p->st.x64[2] += p->st.x64[1];
	p->st.x64[1] = c_hsh_rol64(p->st.x64[1], 17);
	p->st.x64[1] ^= p->st.x64[2];
	p->st.x64[2] = c_hsh_rol64(p->st.x64[2], 32);
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
	u64 k0, k1;

	/* length */
	p->curlen = 0;
	p->len = 0;
	/* key seed */
	k0 = c_uint_64unpack((char *)p->buf);
	k1 = c_uint_64unpack((char *)(p->buf + 8));
	/* v[0-3] */
	p->st.x64[0] = k0 ^ 0x736f6d6570736575;
	p->st.x64[1] = k1 ^ 0x646f72616e646f6d;
	p->st.x64[2] = k0 ^ 0x6c7967656e657261;
	p->st.x64[3] = k1 ^ 0x7465646279746573;
}

static void
compress(ctype_hst *p, char *data)
{
	u64 x;
	x = c_uint_64unpack(data);
	p->st.x64[3] ^= x;
	sipround2(p); /* cround */
	p->st.x64[0] ^= x;
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 8, p, data, n);
}

static void
end(ctype_hst *p, char *s)
{
	u64 r;

	p->len += p->curlen << 3;
	r = c_hsh_octets(p) << 56;

	switch (p->curlen) {
	case 7:
		r |= (u64)p->buf[6] << 48;
		/* FALLTHROUGH */
	case 6:
		r |= (u64)p->buf[5] << 40;
		/* FALLTHROUGH */
	case 5:
		r |= (u64)p->buf[4] << 32;
		/* FALLTHROUGH */
	case 4:
		r |= (u64)p->buf[3] << 24;
		/* FALLTHROUGH */
	case 3:
		r |= (u64)p->buf[2] << 16;
		/* FALLTHROUGH */
	case 2:
		r |= (u64)p->buf[1] << 8;
		/* FALLTHROUGH */
	case 1:
		r |= (u64)p->buf[0];
	}

	p->st.x64[3] ^= r;
	sipround2(p); /* cround */
	p->st.x64[0] ^= r;
	p->st.x64[2] ^= 0xff;
	sipround4(p); /* dround */

	r = p->st.x64[0] ^ p->st.x64[1] ^ p->st.x64[2] ^ p->st.x64[3];
	c_uint_64pack(s, r);
}
