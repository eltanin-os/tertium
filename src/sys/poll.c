#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_poll(ctype_iopause *p, uint n, int t)
{
	return c_std_syscall(SYS_poll, p, n, t);
}
