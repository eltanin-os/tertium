#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tna_now(Taia *t)
{
	Time tm;
	c_sys_gettime(CLOCK_REALTIME, &tm);
	t->sec.x = 4611686018427387914ULL + (u64int)tm.tv_sec;
	t->nano  = 1000 * tm.tv_sec + 500;
	t->atto  = 0;
}
