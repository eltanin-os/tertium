#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fchdir(ctype_fd fd)
{
	ctype_status r;

	do {
		r = c_std_syscall(SYS_fchdir, fd);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
