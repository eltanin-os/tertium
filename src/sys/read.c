#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_read(int f, void *p, usize n)
{
	return c_sys_call(__NR_read, f, p, n);
}
