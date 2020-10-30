#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_now(ctype_tai *t)
{
	ctype_time tm;

	c_sys_clockgettime(CLOCK_REALTIME, &tm);
	t->x = 4611686018427387914ULL + (u64int)tm.sec;
}
