#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_sys_getpid(void)
{
	return c_sys_call(SYS_getpid);
}
