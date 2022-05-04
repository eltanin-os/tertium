#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_uint_16bigpack(char *s, u16 u)
{
	s[1] = u & 255;
	s[0] = u >> 8;
	return s;
}
