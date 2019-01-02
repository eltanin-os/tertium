#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_dup(int f)
{
	return c_sys_call(__NR_dup, f);
}
