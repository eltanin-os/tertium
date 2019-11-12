#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_sys_exit(int r)
{
	c_std_syscall(SYS_exit, r);
}
