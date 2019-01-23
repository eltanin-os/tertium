#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tna_pack(char *s, CTaia *t)
{
	ulong x;
	c_tai_pack(s, &t->sec);
	s += 8;
	x = t->atto;
	s[7] = x & 255; x >>= 8;
	s[6] = x & 255; x >>= 8;
	s[5] = x & 255; x >>= 8;
	s[4] = x;
	x = t->nano;
	s[3] = x & 255; x >>= 8;
	s[2] = x & 255; x >>= 8;
	s[1] = x & 255; x >>= 8;
	s[0] = x;
}
