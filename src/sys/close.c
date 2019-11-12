#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_close(ctype_fd fd)
{
	ctype_status r;

	do {
		r = c_std_syscall(SYS_close, fd);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
