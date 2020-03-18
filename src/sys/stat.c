#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_stat(ctype_stat *p, char *s)
{
	return c_std_syscall(SYS_fstatat, AT_FDCWD, s, p, 0);
}
