#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_write(int f, void *p, usize n)
{
	return c_sys_call(__NR_write, f, p, n);
}
