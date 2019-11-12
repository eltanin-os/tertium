#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fchmod(int fd, uint mode)
{
	int r;

	do {
		r = c_std_syscall(SYS_fchmod, fd, mode);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
