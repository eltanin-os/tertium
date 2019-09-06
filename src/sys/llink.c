#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_llink(char *oldpath, char *newpath)
{
	return c_sys_call(SYS_linkat, AT_FDCWD, oldpath, AT_FDCWD, newpath);
}
