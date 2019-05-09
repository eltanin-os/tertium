#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_uint_16unpack(char *s, u16int *u)
{
	u16int r;
	r   = (uchar)s[1];
	r <<= 8;
	r  += (uchar)s[0];
	*u  = r;
}
