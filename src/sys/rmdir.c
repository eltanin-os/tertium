#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_rmdir(char *s)
{
	return c_sys_call(__NR_rmdir, s);
}