#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fstat(CStat *p, int f)
{
	if (c_sys_call(SYS_fstat, f, p) < 0)
		return -1;

	return 0;
}
