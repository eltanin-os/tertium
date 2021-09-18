#include <tertium/cpu.h>
#include <tertium/std.h>

#if C_HAS_PIPE2
ctype_status
c_nix_pipe2(ctype_fd *fds, uint opts)
{
	return c_sys_pipe2(fds, opts);
}
#else
#error "TODO: implement pipe2"
#endif
