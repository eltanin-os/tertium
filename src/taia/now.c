#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_now(ctype_taia *t)
{
	ctype_time tm;

	c_sys_call(SYS_clock_gettime, CLOCK_REALTIME, &tm);
	t->sec.x = 4611686018427387914ULL + (u64int)tm.sec;
	t->nano = 1000 * tm.sec + 500;
	t->atto = 0;
}
