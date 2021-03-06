#include <tertium/cpu.h>
#include <tertium/std.h>

struct rand {
	u64int state;
	u64int inc;
};

static int haveseed;

u32int
rng(struct rand *p)
{
	u64int os;
	u32int xs, rot;

	os = p->state;
	p->state = os * 6364136223846793005ULL + (p->inc | 1);
	xs = ((os >> 18) ^ os) >> 27;
	rot = os >> 59;
	return (xs >> rot) | (xs << ((-rot) & 31));
}

char *
c_rand_data(char *s, usize n)
{
	static struct rand rst;
	u64int seed[2];
	u32int x;
	u8int r;

	if (!haveseed) {
		c_rand_genseed((void *)seed, sizeof(seed));
		rst.state = seed[0];
		rst.inc = seed[1];
		++haveseed;
	}
	while (n) {
		n -= r = C_MIN(n, 4);
		x = rng(&rst);
		c_mem_cpy(s + n, r, &x);
	}
	return s;
}
