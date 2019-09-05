#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_now(CTai *t)
{
	__fb_time tm;

	c_sys_call(SYS_clock_gettime, CLOCK_REALTIME, &tm);
	t->x = 4611686018427387914ULL + (u64int)tm.tv_sec;
}
