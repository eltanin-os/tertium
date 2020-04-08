#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define F(a,b,c) (c ^ (a & (b ^ c)))
#define G(a,b,c) (b ^ (c & (b ^ a)))
#define H(a,b,c) (a^b^c)
#define I(a,b,c) (b^(a|(~c)))

#define FF(a,b,c,d,M,s,t) \
{ a = (a + F(b,c,d) + M + t); a = ROL(a, s) + b; }
#define GG(a,b,c,d,M,s,t) \
{ a = (a + G(b,c,d) + M + t); a = ROL(a, s) + b; }
#define HH(a,b,c,d,M,s,t) \
{ a = (a + H(b,c,d) + M + t); a = ROL(a, s) + b; }
#define II(a,b,c,d,M,s,t) \
{ a = (a + I(b,c,d) + M + t); a = ROL(a, s) + b; }

#define ROL(a, b) __hsh_rol32((a), (b))
#define REV(a,b,c,d,t) { t=d; d=c; c=b; b=a; a=t; }

static uchar wtab[64] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
	1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
	5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
	0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9
};

static uchar rtab[64] = {
	7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
	5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
	6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

static u32int ktab[64] = {
	0xD76AA478UL, 0xE8C7B756UL, 0x242070DBUL,
	0xC1BDCEEEUL, 0xF57C0FAFUL, 0x4787C62AUL,
	0xA8304613UL, 0xFD469501UL, 0x698098D8UL,
	0x8B44F7AFUL, 0xFFFF5BB1UL, 0x895CD7BEUL,
	0x6B901122UL, 0xFD987193UL, 0xA679438EUL,
	0x49B40821UL, 0xF61E2562UL, 0xC040B340UL,
	0x265E5A51UL, 0xE9B6C7AAUL, 0xD62F105DUL,
	0x02441453UL, 0xD8A1E681UL, 0xE7D3FBC8UL,
	0x21E1CDE6UL, 0xC33707D6UL, 0xF4D50D87UL,
	0x455A14EDUL, 0xA9E3E905UL, 0xFCEFA3F8UL,
	0x676F02D9UL, 0x8D2A4C8AUL, 0xFFFA3942UL,
	0x8771F681UL, 0x6D9D6122UL, 0xFDE5380CUL,
	0xA4BEEA44UL, 0x4BDECFA9UL, 0xF6BB4B60UL,
	0xBEBFBC70UL, 0x289B7EC6UL, 0xEAA127FAUL,
	0xD4EF3085UL, 0x04881D05UL, 0xD9D4D039UL,
	0xE6DB99E5UL, 0x1FA27CF8UL, 0xC4AC5665UL,
	0xF4292244UL, 0x432AFF97UL, 0xAB9423A7UL,
	0xFC93A039UL, 0x655B59C3UL, 0x8F0CCC92UL,
	0xFFEFF47DUL, 0x85845DD1UL, 0x6FA87E4FUL,
	0xFE2CE6E0UL, 0xA3014314UL, 0x4E0811A1UL,
	0xF7537E82UL, 0xBD3AF235UL, 0x2AD7D2BBUL,
	0xEB86D391UL,
};

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *);
static void digest(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
	&digest,
};

ctype_hmd *c_hsh_md5 = &md;

static void
init(ctype_hst *p)
{
	p->len = 0;
	p->st.x32[0] = 0x67452301UL;
	p->st.x32[1] = 0xEFCDAB89UL;
	p->st.x32[2] = 0x98BADCFEUL;
	p->st.x32[3] = 0x10325476UL;
}

static void
compress(ctype_hst *p, char *data)
{
	u32int st[4], w[16];
	u32int i, t;

	for (i = 0; i < 16; ++i)
		w[i] = c_uint_32unpack(data + (i << 2));

	st[0] = p->st.x32[0];
	st[1] = p->st.x32[1];
	st[2] = p->st.x32[2];
	st[3] = p->st.x32[3];
	for (i = 0; i < 16; ++i) {
		FF(st[0], st[1], st[2], st[3], w[wtab[i]], rtab[i], ktab[i]);
		REV(st[0], st[1], st[2], st[3], t);
	}
	for (; i < 32; ++i) {
		GG(st[0], st[1], st[2], st[3], w[wtab[i]], rtab[i], ktab[i]);
		REV(st[0], st[1], st[2], st[3], t);
	}
	for (; i < 48; ++i) {
		HH(st[0], st[1], st[2], st[3], w[wtab[i]], rtab[i], ktab[i]);
		REV(st[0], st[1], st[2], st[3], t);
	}
	for (; i < 64; ++i) {
		II(st[0], st[1], st[2], st[3], w[wtab[i]], rtab[i], ktab[i]);
		REV(st[0], st[1], st[2], st[3], t);
	}
	p->st.x32[0] += st[0];
	p->st.x32[1] += st[1];
	p->st.x32[2] += st[2];
	p->st.x32[3] += st[3];
}

static void
update(ctype_hst *p, char *data, usize n)
{
	__hsh_update(compress, 64, p, data, n);
}

static void
end(ctype_hst *p)
{
	uint r;

	r = p->len % 64;
	p->buf[r++] = 0x80;

	if (r > 56) {
		c_mem_set(p->buf + r, 64 - r, 0);
		compress(p, (char *)p->buf);
		r = 0;
	}
	c_mem_set(p->buf + r, 56 - r, 0);
	c_uint_64pack((char *)p->buf + 56, p->len << 3);
	compress(p, (char *)p->buf);
}

static void
digest(ctype_hst *p, char *s)
{
	int i;

	for (i = 0; i < 4; i++)
		c_uint_32pack(s + (i << 2), p->st.x32[i]);
}
