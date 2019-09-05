#include <tertium/cpu.h>
#include <tertium/std.h>

u64int
c_uint_64bigunpack(char *s)
{
	u64int r;

	r = (uchar)s[0];
	r <<= 8;
	r += (uchar)s[1];
	r <<= 8;
	r += (uchar)s[2];
	r <<= 8;
	r += (uchar)s[3];
	r <<= 8;
	r += (uchar)s[4];
	r <<= 8;
	r += (uchar)s[5];
	r <<= 8;
	r += (uchar)s[6];
	r <<= 8;
	r += (uchar)s[7];
	return r;
}
