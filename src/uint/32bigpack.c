#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_uint_32bigpack(char *s, u32int u)
{
	s[3] = u & 255;
	u >>= 8;
	s[2] = u & 255;
	u >>= 8;
	s[1] = u & 255;
	s[0] = u >> 8;
	return s;
}
