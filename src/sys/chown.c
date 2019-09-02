#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_chown(char *s, uint uid, uint gid)
{
	return c_sys_call(SYS_chown, s, uid, gid);
}
