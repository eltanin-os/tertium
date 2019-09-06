#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_chown(char *s, ctype_id uid, ctype_id gid)
{
	return c_sys_call(SYS_chown, s, uid, gid);
}
