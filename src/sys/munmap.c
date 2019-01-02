#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_munmap(void *p, usize n)
{
	return c_sys_call(__NR_munmap, p, n);
}
