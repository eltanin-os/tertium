#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdchmod(ctype_fd fd, uint mode)
{
	ctype_status r;

	do {
		r = c_sys_fchmod(fd, mode);
	} while ((r < 0) && errno == C_ERR_EINTR);

	return r;
}
