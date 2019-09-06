#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_tai(ctype_taia *ta, ctype_tai *t)
{
	*t = ta->sec;
}
