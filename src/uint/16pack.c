#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_uint_16pack(char *s, u16 u)
{
	s[0] = u & 255;
	s[1] = u >> 8;
	return s;
}
