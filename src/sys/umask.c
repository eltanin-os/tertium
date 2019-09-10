#include <tertium/cpu.h>
#include <tertium/std.h>

uint
c_sys_umask(uint m)
{
	return c_sys_call(SYS_umask, m);
}
