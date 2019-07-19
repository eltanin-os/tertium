#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_now(CTai *t)
{
	CTime tm;
	c_sys_gettime(CLOCK_REALTIME, &tm);
	t->x =  4611686018427387914ULL + (u64int)tm.sec;
}
