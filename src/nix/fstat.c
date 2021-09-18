#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdstat(ctype_stat *p, ctype_fd fd)
{
	return c_sys_fstat(fd, p);
}
