#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_open(char *s, int f, int m)
{
	return c_sys_call(__NR_open, s, f, m);
}
