#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_pack(char *s, ctype_tai *t)
{
	c_uint_64bigpack(s, t->x);
}
