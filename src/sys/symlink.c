#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_symlink(char *target, char *path)
{
	return c_sys_call(SYS_symlink, target, path);
}