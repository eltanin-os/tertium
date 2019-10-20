#include <tertium/cpu.h>
#include <tertium/std.h>

#define F(x) ((x) * 1493)
#define AVALANCHE() \
{\
	r ^= r << 16; r += r << 13; r ^= r >> 7; \
	r += r <<  9; r ^= r >>  8; r += r << 2; \
}

char *
c_rand_genseed(char *s, usize n)
{
	ctype_time tm;
	u64int r;

	c_sys_call(SYS_clock_gettime, CLOCK_REALTIME, &tm);
	r = F(F(F(F(F(tm.nsec)) + c_sys_getpid()) + (uintptr)s) + (uintptr)&n);
	AVALANCHE();

	while (n) {
		n -= 8;
		c_uint_64bigpack(s + n, r);
		r = F(r ^ (n << 2));
	}

	return s;
}
