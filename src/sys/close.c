#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_close(int f)
{
	return c_sys_call(__NR_close, f);
}
