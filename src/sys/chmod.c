#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_chmod(char *s, uint mode)
{
	return c_sys_call(SYS_chmod, s, mode);
}
