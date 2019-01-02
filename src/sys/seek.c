#include <tertium/cpu.h>
#include <tertium/std.h>

vlong
c_sys_seek(int f, vlong o, int w)
{
	return c_sys_call(__NR_lseek, f, o, w);
}
