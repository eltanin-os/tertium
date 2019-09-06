#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_mkdir(char *path, uint mode)
{
	return c_sys_call(SYS_mkdir, path, mode);
}
