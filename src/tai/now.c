#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_now(ctype_tai *t)
{
	CTime tm;

	c_sys_call(SYS_clock_gettime, CLOCK_REALTIME, &tm);
	t->x = 4611686018427387914ULL + (u64int)tm.sec;
}
