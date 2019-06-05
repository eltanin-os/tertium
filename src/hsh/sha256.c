#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define Ch(a,b,c)  (c ^ (a & (b ^ c)))
#define Maj(a,b,c) ((a & b) | (c & (a | b)))
#define R(a,b)     (((a)&0xFFFFFFFF)>>(b))
#define G0(x)      (ROR(x, 7)  ^ ROR(x, 18) ^ R(x, 3))
#define G1(x)      (ROR(x, 17) ^ ROR(x, 19) ^ R(x, 10))
#define S0(x)      (ROR(x, 2)  ^ ROR(x, 13) ^ ROR(x, 22))
#define S1(x)      (ROR(x, 6)  ^ ROR(x, 11) ^ ROR(x, 25))

#define ROR(a, b) __hsh_ror32((a), (b))
#define REV(a,b,c,d,e,f,g,h,t) { t=h; h=g; g=f; f=e; e=d; d=c; c=b; b=a; a=t; }

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

CHmd *c_hsh_sha256 = &md;

static u32int K[] = {
	0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL, 0x3956c25bUL,
	0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL, 0xd807aa98UL, 0x12835b01UL,
	0x243185beUL, 0x550c7dc3UL, 0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL,
	0xc19bf174UL, 0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
	0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL, 0x983e5152UL,
	0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL, 0xc6e00bf3UL, 0xd5a79147UL,
	0x06ca6351UL, 0x14292967UL, 0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL,
	0x53380d13UL, 0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
	0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL, 0xd192e819UL,
	0xd6990624UL, 0xf40e3585UL, 0x106aa070UL, 0x19a4c116UL, 0x1e376c08UL,
	0x2748774cUL, 0x34b0bcb5UL, 0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL,
	0x682e6ff3UL, 0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
	0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};


static void
init(CHst *p)
{
	p->len = 0;
	p->st.x32[0] = 0x6A09E667UL;
	p->st.x32[1] = 0xBB67AE85UL;
	p->st.x32[2] = 0x3C6EF372UL;
	p->st.x32[3] = 0xA54FF53AUL;
	p->st.x32[4] = 0x510E527FUL;
	p->st.x32[5] = 0x9B05688CUL;
	p->st.x32[6] = 0x1F83D9ABUL;
	p->st.x32[7] = 0x5BE0CD19UL;
}

static void
compress(CHst *p, char *data)
{
	u32int w[64], st[8];
	u32int t0, t1;
	u32int t;
	int i;

	for (i = 0; i < 16; i++)
		w[i] = c_uint_32bigunpack(data + i * 4);

	for (i = 16; i < 64; i++)
		w[i] = G1(w[i - 2]) + w[i - 7] + G0(w[i - 15]) + w[i - 16];

	st[0] = p->st.x32[0];
	st[1] = p->st.x32[1];
	st[2] = p->st.x32[2];
	st[3] = p->st.x32[3];
	st[4] = p->st.x32[4];
	st[5] = p->st.x32[5];
	st[6] = p->st.x32[6];
	st[7] = p->st.x32[7];

	for (i = 0; i < 64; i++) {
		t0 = st[7] + S1(st[4]) + Ch(st[4], st[5], st[6]) + K[i] + w[i];
		t1 = S0(st[0]) + Maj(st[0], st[1], st[2]);
		st[3] += t0;
		st[7]  = t0 + t1;
		REV(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7], t);
	}

	p->st.x32[0] += st[0];
	p->st.x32[1] += st[1];
	p->st.x32[2] += st[2];
	p->st.x32[3] += st[3];
	p->st.x32[4] += st[4];
	p->st.x32[5] += st[5];
	p->st.x32[6] += st[6];
	p->st.x32[7] += st[7];
}

static void
update(CHst *p, char *data, usize n)
{
	__hsh_update(compress, 64, p, data, n);
}

static void
end(CHst *p)
{
	uint r;

	r = p->len % 64;
	p->buf[r++] = 0x80;

	if (r > 56) {
		c_mem_set(p->buf + r, 64 - r, 0);
		compress(p, p->buf);
		r = 0;
	}

	c_mem_set(p->buf + r, 56 - r, 0);
	c_uint_64bigpack(p->buf + 56, p->len * 8);
	compress(p, p->buf);
}

static void
digest(CHst *p, char *s)
{
	int i;
	for (i = 0; i < 8; i++)
		c_uint_32bigpack(s + i * 4, p->st.x32[i]);
}
