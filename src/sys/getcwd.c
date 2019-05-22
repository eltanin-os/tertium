#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_sys_getcwd(char *s, usize n)
{
	return c_sys_call(SYS_getcwd, s, n) < 0 ? nil : s;
}
