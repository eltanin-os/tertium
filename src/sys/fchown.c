#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fchown(ctype_fd fd, ctype_id uid, ctype_id gid)
{
	ctype_status r;

	do {
		r = c_std_syscall(SYS_fchown, fd, uid, gid);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
