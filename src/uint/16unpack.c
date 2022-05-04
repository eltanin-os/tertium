#include <tertium/cpu.h>
#include <tertium/std.h>

u16
c_uint_16unpack(char *s)
{
	u16 r;

	r = (uchar)s[1];
	r <<= 8;
	r += (uchar)s[0];
	return r;
}
