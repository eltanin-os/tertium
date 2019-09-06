#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_unpack(char *s, ctype_tai *t)
{
	u64int x;

	x = t->x;
	x <<= 8;
	x += (uchar)s[1];
	x <<= 8;
	x += (uchar)s[2];
	x <<= 8;
	x += (uchar)s[3];
	x <<= 8;
	x += (uchar)s[4];
	x <<= 8;
	x += (uchar)s[5];
	x <<= 8;
	x += (uchar)s[6];
	x <<= 8;
	x += (uchar)s[7];
	t->x = x;
}
