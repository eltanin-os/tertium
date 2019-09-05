#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define Ch(a,b,c)  ((c ^ (a & (b ^ c))))
#define Maj(a,b,c) ((a & b) | (c & (a | b)))
#define R(a, b)    (((a)&0xFFFFFFFFFFFFFFFFULL)>>((u64int)b))
#define G0(x)      (ROR(x, 1)  ^ ROR(x, 8)  ^ R(x, 7))
#define G1(x)      (ROR(x, 19) ^ ROR(x, 61) ^ R(x, 6))
#define S0(x)      (ROR(x, 28) ^ ROR(x, 34) ^ ROR(x, 39))
#define S1(x)      (ROR(x, 14) ^ ROR(x, 18) ^ ROR(x, 41))

#define ROR(a, b) __hsh_ror64((a), (b))
#define REV(a,b,c,d,e,f,g,h) { h=g; g=f; f=e; e=d+t0; d=c; c=b; b=a; a=t0+t1; }

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

CHmd *c_hsh_sha512 = &md;

static u64int K[] = {
	0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
	0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
	0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
	0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
	0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
	0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
	0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
	0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
	0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
	0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
	0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
	0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
	0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
	0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
	0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
	0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
	0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
	0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
	0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
	0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
	0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
	0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
	0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
	0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
	0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
	0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
	0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
	0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
	0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
	0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
	0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
	0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
	0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
	0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
	0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
	0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
	0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
	0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
	0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
	0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

static void
init(CHst *p)
{
	p->len = 0;
	p->st.x64[0] = 0x6a09e667f3bcc908ULL;
	p->st.x64[1] = 0xbb67ae8584caa73bULL;
	p->st.x64[2] = 0x3c6ef372fe94f82bULL;
	p->st.x64[3] = 0xa54ff53a5f1d36f1ULL;
	p->st.x64[4] = 0x510e527fade682d1ULL;
	p->st.x64[5] = 0x9b05688c2b3e6c1fULL;
	p->st.x64[6] = 0x1f83d9abfb41bd6bULL;
	p->st.x64[7] = 0x5be0cd19137e2179ULL;
}

static void
compress(CHst *p, char *data)
{
	u64int w[80], st[8];
	u64int t0, t1;
	int i;

	for (i = 0; i < 16; i++)
		w[i] = c_uint_64bigunpack(data + i * 8);

	for (i = 16; i < 80; i++)
		w[i] = G1(w[i - 2]) + w[i - 7] + G0(w[i - 15]) + w[i - 16];

	st[0] = p->st.x64[0];
	st[1] = p->st.x64[1];
	st[2] = p->st.x64[2];
	st[3] = p->st.x64[3];
	st[4] = p->st.x64[4];
	st[5] = p->st.x64[5];
	st[6] = p->st.x64[6];
	st[7] = p->st.x64[7];

	for (i = 0; i < 80; i++) {
		t0 = st[7] + S1(st[4]) + Ch(st[4], st[5], st[6]) + K[i] + w[i];
		t1 = S0(st[0]) + Maj(st[0], st[1], st[2]);
		REV(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7]);
	}

	p->st.x64[0] += st[0];
	p->st.x64[1] += st[1];
	p->st.x64[2] += st[2];
	p->st.x64[3] += st[3];
	p->st.x64[4] += st[4];
	p->st.x64[5] += st[5];
	p->st.x64[6] += st[6];
	p->st.x64[7] += st[7];
}

static void
update(CHst *p, char *data, usize n)
{
	__hsh_update(compress, 128, p, data, n);
}

static void
end(CHst *p)
{
	uint r;

	r = p->len % 128;
	p->buf[r++] = 0x80;

	if (r > 112) {
		c_mem_set(p->buf + r, 128 - r, 0);
		compress(p, (char *)p->buf);
		r = 0;
	}

	c_mem_set(p->buf + r, 120 - r, 0);
	c_uint_64bigpack((char *)p->buf + 120, p->len * 8);
	compress(p, (char *)p->buf);
}

static void
digest(CHst *p, char *s)
{
	int i;

	for (i = 0; i < 8; i++)
		c_uint_64bigpack(s + i * 8, p->st.x64[i]);
}
