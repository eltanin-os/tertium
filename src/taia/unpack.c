#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_unpack(ctype_taia *t, char *s)
{
	c_tai_unpack(&t->sec, s);
	t->nano = c_uint_32bigunpack(s + 8);
	t->atto = c_uint_32bigunpack(s + 12);
}
