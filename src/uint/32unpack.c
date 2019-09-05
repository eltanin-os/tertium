#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_uint_32unpack(char *s)
{
	u32int r;

	r = (uchar)s[3];
	r <<= 8;
	r += (uchar)s[2];
	r <<= 8;
	r += (uchar)s[1];
	r <<= 8;
	r += (uchar)s[0];
	return r;
}
