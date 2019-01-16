#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tna_unpack(char *s, Taia *t)
{
	ulong x;
	c_tai_unpack(s, &t->sec);
	s += 8;
	x = (unsigned char) s[4];
	x <<= 8; x += (unsigned char) s[5];
	x <<= 8; x += (unsigned char) s[6];
	x <<= 8; x += (unsigned char) s[7];
	t->atto = x;
	x = (unsigned char) s[0];
	x <<= 8; x += (unsigned char) s[1];
	x <<= 8; x += (unsigned char) s[2];
	x <<= 8; x += (unsigned char) s[3];
	t->nano = x;
}
