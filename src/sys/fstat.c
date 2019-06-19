#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fstat(CStat *p, int f)
{
	__fb_stat st;

	if (c_sys_call(SYS_fstat, f, &st) < 0)
		return -1;

	__C_STCOPY(p, st);

	return 0;
}
