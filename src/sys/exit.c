#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_sys_exit(int r)
{
	c_sys_call(SYS_exit, r);
}
