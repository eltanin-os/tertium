#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_mkdir(char *path, ushort mode)
{
	return c_sys_call(SYS_mkdir, path, mode);
}
