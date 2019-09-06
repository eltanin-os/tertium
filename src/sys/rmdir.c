#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_rmdir(char *s)
{
	return c_sys_call(SYS_rmdir, s);
}
