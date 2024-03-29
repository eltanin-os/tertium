#include <tertium/cpu.h>
#include <tertium/std.h>

#define F0(a,b,c) (c ^ (a & (b ^ c)))
#define F1(a,b,c) (a ^ b ^ c)
#define F2(a,b,c) ((a & b) | (c & (a | b)))
#define F3(a,b,c) (a ^ b ^ c)

#define FF0(a,b,c,d,e,i) \
{ e = (ROL(a, 5) + F0(b,c,d) + e + w[i] + 0x5a827999UL); b = ROL(b, 30); }
#define FF1(a,b,c,d,e,i) \
{ e = (ROL(a, 5) + F1(b,c,d) + e + w[i] + 0x6ed9eba1UL); b = ROL(b, 30); }
#define FF2(a,b,c,d,e,i) \
{ e = (ROL(a, 5) + F2(b,c,d) + e + w[i] + 0x8f1bbcdcUL); b = ROL(b, 30); }
#define FF3(a,b,c,d,e,i) \
{ e = (ROL(a, 5) + F3(b,c,d) + e + w[i] + 0xca62c1d6UL); b = ROL(b, 30); }

#define ROL(a, b) c_hsh_rol32((a), (b))
#define REV(a,b,c,d,e,t) { t=e; e=d; d=c; c=b; b=a; a=t; }

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
};

ctype_hmd *c_hsh_sha1 = &md;

static void
init(ctype_hst *p)
{
	p->curlen = 0;
	p->len = 0;
	p->st.x32[0] = 0x67452301UL;
	p->st.x32[1] = 0xefcdab89UL;
	p->st.x32[2] = 0x98badcfeUL;
	p->st.x32[3] = 0x10325476UL;
	p->st.x32[4] = 0xc3d2e1f0UL;
}

static void
compress(ctype_hst *p, char *data)
{
	u32 st[5], w[80];
	u32 t;
	int i;

	for (i = 0; i < 16; ++i)
		w[i] = c_uint_32bigunpack(data + (i << 2));

	for (i = 16; i < 80; ++i)
		w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

	for (i = 0; i < 5; ++i)
		st[i] = p->st.x32[i];

	for (i = 0; i < 20; ++i) {
		FF0(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}
	for (; i < 40; ++i) {
		FF1(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}
	for (; i < 60; ++i) {
		FF2(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}
	for (; i < 80; ++i) {
		FF3(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}

	for (i = 0; i < 5; ++i)
		p->st.x32[i] += st[i];
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 64, p, data, n);
}

static void
end(ctype_hst *p, char *s)
{
	int i;

	p->len += p->curlen << 3;
	p->buf[p->curlen++] = 0x80;
	if (p->curlen > 56) {
		c_mem_set(p->buf + p->curlen, 64 - p->curlen, 0);
		compress(p, (char *)p->buf);
		p->curlen = 0;
	}
	c_mem_set(p->buf + p->curlen, 56 - p->curlen, 0);
	c_uint_64bigpack((char *)p->buf + 56, p->len);
	compress(p, (char *)p->buf);

	for (i = 0; i < 5; ++i)
		c_uint_32bigpack(s + (i << 2), p->st.x32[i]);
}
