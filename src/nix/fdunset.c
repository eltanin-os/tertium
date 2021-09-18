#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdunset(ctype_fd fd, uint flags)
{
	uint opts;

	if ((opts = c_sys_fcntl(fd, C_FGETFD)) == (uint)-1)
		return -1;
	return c_sys_fcntl(fd, C_FSETFD, opts & ~flags);
}
