#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_rename(char *s, char *d)
{
	return c_std_syscall(SYS_rename, s, d);
}
