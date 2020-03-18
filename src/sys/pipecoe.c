#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_pipecoe(ctype_fd *fds)
{
	return c_std_syscall(SYS_pipe2, fds, C_OCEXEC);
}
