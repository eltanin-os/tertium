#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fchdir(int f)
{
	return c_sys_call(__NR_fchdir, f);
}
