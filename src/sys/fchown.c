#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fchown(ctype_fd fd, ctype_id uid, ctype_id gid)
{
	return c_sys_call(SYS_fchown, fd, uid, gid);
}
