#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_sys_getgid(void)
{
	return c_sys_call(SYS_getgid);
}
