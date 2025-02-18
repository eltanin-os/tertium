#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_pack(char *s, ctype_taia *t)
{
	c_tai_pack(s, &t->sec);
	c_uint_32bigpack(s + 8, t->nano);
	c_uint_32bigpack(s + 12, t->atto);
}
