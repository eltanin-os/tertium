#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_now(ctype_taia *t)
{
	ctype_time tm;
	c_nix_gettime(&tm);
	c_taia_fromtime(t, &tm);
}
