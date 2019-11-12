#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_link(char *oldpath, char *newpath)
{
	return c_std_syscall(SYS_link, oldpath, newpath);
}
