#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fchmod(int fd, uint mode)
{
	return c_sys_call(SYS_fchmod, fd, mode);
}
