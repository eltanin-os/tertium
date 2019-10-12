#include <tertium/cpu.h>
#include <tertium/std.h>

#define MIX() \
{\
	r ^= r << 16; r += r << 13; r ^= r >> 7; \
	r += r <<  9; r ^= r >>  8; r += r << 2; \
}

char *
c_rand_genseed(char *s, usize n)
{
	ctype_taia now;
	u64int r;

	c_taia_now(&now);
	r = (u64int)c_taia_approx(&now);
	r = ((r + c_sys_getpid()) * 1493) + (uintptr)s + (uintptr)&n;
	MIX();

	while (n) {
		c_uint_64bigpack(s, r);
		s += 8;
		n -= 8;
		r = (r ^ (n << 2)) * 1493;
	}

	return s;
}
