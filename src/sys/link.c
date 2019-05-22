#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_link(char *oldpath, char *newpath)
{
	return c_sys_call(SYS_link, oldpath, newpath);
}
