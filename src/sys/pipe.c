#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_pipe(ctype_fd fds[2])
{
	return c_sys_call(SYS_pipe, fds);
}
