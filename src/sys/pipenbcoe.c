#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_pipenbcoe(ctype_fd *fds)
{
	return c_sys_pipe2(fds, C_OCEXEC | C_ONONBLOCK);
}
