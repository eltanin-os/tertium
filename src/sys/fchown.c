#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fchown(int fd, uint uid, uint gid)
{
	return c_sys_call(SYS_fchown, fd, uid, gid);
}
