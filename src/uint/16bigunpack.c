#include <tertium/cpu.h>
#include <tertium/std.h>

u16
c_uint_16bigunpack(char *s)
{
	u16 r;

	r = (uchar)s[0];
	r <<= 8;
	r += (uchar)s[1];
	return r;
}
