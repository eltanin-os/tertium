#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_sys_fork(void)
{
	return c_std_syscall(SYS_fork);
}
