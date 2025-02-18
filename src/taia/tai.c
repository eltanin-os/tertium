#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_tai(ctype_taia *taia, ctype_tai *t)
{
	*t = taia->sec;
}
