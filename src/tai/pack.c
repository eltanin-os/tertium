#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_pack(char *s, ctype_tai *t)
{
	u64 x;

	x = t->x;
	s[7] = x & 255;
	x >>= 8;
	s[6] = x & 255;
	x >>= 8;
	s[5] = x & 255;
	x >>= 8;
	s[4] = x & 255;
	x >>= 8;
	s[3] = x & 255;
	x >>= 8;
	s[2] = x & 255;
	x >>= 8;
	s[1] = x & 255;
	x >>= 8;
	s[0] = x;
}
