#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_pipe(ctype_fd *fds)
{
	return c_sys_pipe(fds);
}
