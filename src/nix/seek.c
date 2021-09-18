#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_seek(ctype_fd fd, ctype_fssize off, int w)
{
	return c_sys_lseek(fd, off, w);
}
