#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdchdir(ctype_fd fd)
{
	ctype_status r;

	do {
		r = c_sys_fchdir(fd);
	} while ((r < 0) && errno == C_ERR_EINTR);

	return r;
}
