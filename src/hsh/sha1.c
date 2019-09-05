#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

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

#define ROL(a, b) __hsh_rol32((a), (b))
#define REV(a,b,c,d,e,t) { t=e; e=d; d=c; c=b; b=a; a=t; }

static void init(CHst *);
static void update(CHst *, char *, usize);
static void end(CHst *);
static void digest(CHst *, char *);

static CHmd md = {
	&init,
	&update,
	&end,
	&digest,
};

CHmd *c_hsh_sha1 = &md;

static void
init(CHst *p)
{
	p->len = 0;
	p->st.x32[0] = 0x67452301UL;
	p->st.x32[1] = 0xefcdab89UL;
	p->st.x32[2] = 0x98badcfeUL;
	p->st.x32[3] = 0x10325476UL;
	p->st.x32[4] = 0xc3d2e1f0UL;
}

static void
compress(CHst *p, char *data)
{
	u32int st[5], w[80];
	u32int t;
	int i;

	for (i = 0; i < 16; i++)
		w[i] = c_uint_32bigunpack(data + i * 4);

	for (i = 16; i < 80; i++)
		w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

	st[0] = p->st.x32[0];
	st[1] = p->st.x32[1];
	st[2] = p->st.x32[2];
	st[3] = p->st.x32[3];
	st[4] = p->st.x32[4];

	for (i = 0; i < 20; i++) {
		FF0(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}

	for (; i < 40; i++) {
		FF1(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}

	for (; i < 60; i++) {
		FF2(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}

	for (; i < 80; i++) {
		FF3(st[0], st[1], st[2], st[3], st[4], i);
		REV(st[0], st[1], st[2], st[3], st[4], t);
	}

	p->st.x32[0] += st[0];
	p->st.x32[1] += st[1];
	p->st.x32[2] += st[2];
	p->st.x32[3] += st[3];
	p->st.x32[4] += st[4];
}

static void
update(CHst *p, char *data, usize n)
{
	__hsh_update(compress, 64, p, data, n);
}

static void
end(CHst *p)
{
	unsigned r;

	r = p->len % 64;
	p->buf[r++] = 0x80;

	if (r > 56) {
		c_mem_set(p->buf + r, 64 - r, 0);
		compress(p, (char *)p->buf);
		r = 0;
	}

	c_mem_set(p->buf + r, 56 - r, 0);
	c_uint_64bigpack((char *)p->buf + 56, p->len * 8);
	compress(p, (char *)p->buf);
}

static void
digest(CHst *p, char *s)
{
	int i;

	for (i = 0; i < 5; i++)
		c_uint_32bigpack(s + i * 4, p->st.x32[i]);
}
