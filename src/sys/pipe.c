#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_pipe(ctype_fd *fds)
{
	return c_std_syscall(SYS_pipe, fds);
}
