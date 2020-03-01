#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_pipe2(ctype_fd *fds, uint opts)
{
	return c_std_syscall(SYS_pipe2, fds, opts);
}
