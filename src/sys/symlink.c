#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_symlink(char *target, char *path)
{
	return c_std_syscall(SYS_symlink, target, path);
}
