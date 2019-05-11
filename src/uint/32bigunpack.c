#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_uint_32bigunpack(char *s)
{
	u32int r;
	r   = (uchar)s[0];
	r <<= 8;
	r  += (uchar)s[1];
	r <<= 8;
	r  += (uchar)s[2];
	r <<= 8;
	r  += (uchar)s[3];
	return r;
}
