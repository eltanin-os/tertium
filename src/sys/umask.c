#include <tertium/cpu.h>
#include <tertium/std.h>

uint
c_sys_umask(uint m)
{
	return c_std_syscall(SYS_umask, m);
}
