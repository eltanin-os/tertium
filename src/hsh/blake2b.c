#include <tertium/cpu.h>
#include <tertium/std.h>

#define ROR64(a, b) c_hsh_ror64((a), (b))

#define G(r, i, a, b, c, d)             \
do {                                    \
 a = a + b + m[sigma[r][(i << 1) + 0]]; \
 d = ROR64(d ^ a, 32);                  \
 c = c + d;                             \
 b = ROR64(b ^ c, 24);                  \
 a = a + b + m[sigma[r][(i << 1) + 1]]; \
 d = ROR64(d ^ a, 16);                  \
 c = c + d;                             \
 b = ROR64(b ^ c, 63);                  \
} while (0)

#define ROUND(r)                    \
do {                                \
 G(r, 0, v[0], v[4], v[8], v[12]);  \
 G(r, 1, v[1], v[5], v[9], v[13]);  \
 G(r, 2, v[2], v[6], v[10], v[14]); \
 G(r, 3, v[3], v[7], v[11], v[15]); \
 G(r, 4, v[0], v[5], v[10], v[15]); \
 G(r, 5, v[1], v[6], v[11], v[12]); \
 G(r, 6, v[2], v[7], v[8], v[13]);  \
 G(r, 7, v[3], v[4], v[9], v[14]);  \
} while(0)

static const u8 sigma[12][16] = {
	{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
	{ 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 },
	{ 11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4 },
	{  7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8 },
	{  9,  0,  5,  7,  2,  4, 10, 15, 14,  1, 11, 12,  6,  8,  3, 13 },
	{  2, 12,  6, 10,  0, 11,  8,  3,  4, 13,  7,  5, 15, 14,  1,  9 },
	{ 12,  5,  1, 15, 14, 13,  4, 10,  0,  7,  6,  3,  9,  2,  8, 11 },
	{ 13, 11,  7, 14, 12,  1,  3,  9,  5,  0, 15,  4,  8,  6,  2, 10 },
	{  6, 15, 14,  9, 11,  3,  0,  8, 12,  2, 13,  7,  1,  4, 10,  5 },
	{ 10,  2,  8,  4,  7,  6,  1,  5, 15, 11,  9, 14,  3, 12, 13 , 0 },
	{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
	{ 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 },
};

static void init256(ctype_hst *);
static void init512(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end256(ctype_hst *, char *);
static void end512(ctype_hst *, char *);

static ctype_hmd md256 = {
	&init256,
	&update,
	&end256,
};

static ctype_hmd md512 = {
	&init512,
	&update,
	&end512,
};

ctype_hmd *c_hsh_blake2b256 = &md256;
ctype_hmd *c_hsh_blake2b512 = &md512;

static void
init(ctype_hst *p, usize len)
{
	u64 tmp;
	int i;
	uchar P[64];
	/* context init */
	p->curlen = 0;
	p->len = 0;
	/* init0 */
	p->st.x64[0] = 0x6A09E667F3BCC908;
	p->st.x64[1] = 0xBB67AE8584CAA73B;
	p->st.x64[2] = 0x3C6EF372FE94F82B;
	p->st.x64[3] = 0xA54FF53A5F1D36F1;
	p->st.x64[4] = 0x510E527FADE682D1;
	p->st.x64[5] = 0x9B05688C2B3E6C1F;
	p->st.x64[6] = 0x1F83D9ABFB41BD6B;
	p->st.x64[7] = 0x5BE0CD19137E2179;
	/* param init */
	c_mem_set(P, sizeof(P), 0);
	P[0] = (uchar)len; /* digest length */
	P[1] = 0; /* key length */
	P[2] = 1; /* fanout */
	P[3] = 1; /* depth */
	for (i = 0; i < 8; ++i) {
		tmp = c_uint_64unpack((char *)(P + (i << 3)));
		p->st.x64[i] ^= tmp;
	}
	/* TODO: key */
}

static void
init256(ctype_hst *p)
{
	init(p, 32);
}

static void
init512(ctype_hst *p)
{
	init(p, 64);
}

static void
docompress(ctype_hst *p, char *data, u64 last)
{
	u64 m[16];
	u64 v[16];
	uint i;

	for (i = 0; i < 16; ++i) m[i] = c_uint_64unpack(data + (i << 3));
	for (i = 0; i < 8; ++i) v[i] = p->st.x64[i];

	v[8] = 0x6A09E667F3BCC908;
	v[9] = 0xBB67AE8584CAA73B;
	v[10] = 0x3C6EF372FE94F82B;
	v[11] = 0xA54FF53A5F1D36F1;
	v[12] = 0x510E527FADE682D1 ^ (p->len & 0xFFFFFFFF);
	v[13] = 0x9B05688C2B3E6C1F ^ (p->len >> 32);
	v[14] = 0x1F83D9ABFB41BD6B ^ last;
	v[15] = 0x5BE0CD19137E2179;

	ROUND(0);
	ROUND(1);
	ROUND(2);
	ROUND(3);
	ROUND(4);
	ROUND(5);
	ROUND(6);
	ROUND(7);
	ROUND(8);
	ROUND(9);
	ROUND(10);
	ROUND(11);

	for (i = 0; i < 8; ++i) p->st.x64[i] = p->st.x64[i] ^ v[i] ^ v[i + 8];
}

static void
compress(ctype_hst *p, char *data)
{
	docompress(p, data, 0);
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 128, p, data, n);
}

static void
end(ctype_hst *p)
{
	c_mem_set(p->buf + p->curlen, 128 - p->curlen, 0);
	p->len += p->curlen;
	docompress(p, (char *)p->buf, 0xFFFFFFFFFFFFFFFF);
}

static void
end256(ctype_hst *p, char *s)
{
	int i;
	end(p);
	for (i = 0; i < 4; ++i) c_uint_64pack(s + (i << 3), p->st.x64[i]);
}

static void
end512(ctype_hst *p, char *s)
{
	int i;
	end(p);
	for (i = 0; i < 8; ++i) c_uint_64pack(s + (i << 3), p->st.x64[i]);
}
