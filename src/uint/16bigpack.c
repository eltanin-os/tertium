#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_uint_16bigpack(char *s, u16int u)
{
	s[1] = u & 255;
	s[0] = u >> 8;
}
