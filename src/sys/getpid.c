#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_sys_getpid(void)
{
	return c_std_syscall(SYS_getpid);
}
