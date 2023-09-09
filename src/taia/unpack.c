#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_unpack(ctype_taia *t, char *s)
{
	ulong x;

	c_tai_unpack(&t->sec, s);
	s += 8;

	x = (unsigned char)s[4];
	x <<= 8;
	x += (unsigned char)s[5];
	x <<= 8;
	x += (unsigned char)s[6];
	x <<= 8;
	x += (unsigned char)s[7];
	t->atto = x;

	x = (unsigned char)s[0];
	x <<= 8;
	x += (unsigned char)s[1];
	x <<= 8;
	x += (unsigned char)s[2];
	x <<= 8;
	x += (unsigned char)s[3];
	t->nano = x;
}
