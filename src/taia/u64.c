#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_u64(ctype_taia *t, u64 u)
{
	t->sec.x = u;
	t->nano = 0;
	t->atto = 0;
}
