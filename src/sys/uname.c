#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_uname(ctype_utsname *p)
{
	return c_sys_call(SYS_uname, p);
}
