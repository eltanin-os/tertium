#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_now(ctype_taia *t)
{
	ctype_time tm;

	c_nix_gettime(&tm);
	t->sec.x = 4611686018427387914ULL + (u64int)tm.sec;
	t->nano = tm.nsec;
	t->atto = 0;
}
