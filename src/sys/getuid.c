#include <tertium/cpu.h>
#include <tertium/std.h>

uint
c_sys_getuid(void)
{
	return c_sys_call(SYS_getuid);
}
