#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_uint_16pack(char *s, u16int u)
{
	s[0] = u & 255;
	s[1] = u >> 8;
}
