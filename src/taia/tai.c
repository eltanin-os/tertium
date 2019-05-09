#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_tai(CTaia *ta, CTai *t)
{
	*t = ta->sec;
}
