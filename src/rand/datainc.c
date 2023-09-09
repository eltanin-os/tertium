#include <tertium/cpu.h>
#include <tertium/std.h>

static u64 _tertium_rand_const = 0x19D699A5; /* !!! */

static u32
rng(ctype_rst *p)
{
	u64 x;
	x = p->state;
	p->state = x * 6364136223846793005u + _tertium_rand_const;
	return c_hsh_ror32(((x >> 18) ^ x) >> 27, x >> 59);
}

char *
c_rand_datainc(ctype_rst *p, char *s, usize n)
{
	u32 x;
	u8 r;

	while (n) {
		n -= r = C_STD_MIN(n, sizeof(u32));
		x = rng(p);
		c_mem_cpy(s + n, &x, r);
	}
	return s;
}
