#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_uint_32bigunpack(char *s, u32int *u)
{
	u32int r;
	r   = (uchar)s[0];
	r <<= 8;
	r  += (uchar)s[1];
	r <<= 8;
	r  += (uchar)s[2];
	r <<= 8;
	r  += (uchar)s[3];
	*u  = r;
}
