#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fssize
c_sys_seek(ctype_fd fd, ctype_fssize off, int whence)
{
	return c_sys_call(SYS_lseek, fd, off, whence);
}
