#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_gettime(int id, CTime *t)
{
	__fb_time tp;

	if (c_sys_call(SYS_clock_gettime, id, &tp) < 0)
		return -1;

	t->sec = tp.tv_sec;
	t->nsec = tp.tv_nsec;

	return 0;
}
