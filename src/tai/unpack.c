#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_unpack(ctype_tai *t, char *s)
{
	t->x = c_uint_64bigunpack(s);
}
