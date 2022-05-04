#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_uint_32pack(char *s, u32 u)
{
	s[0] = u & 255;
	u >>= 8;
	s[1] = u & 255;
	u >>= 8;
	s[2] = u & 255;
	s[3] = u >> 8;
	return s;
}
