#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_dup2(ctype_fd ofd, ctype_fd nfd)
{
	ctype_status r;

	do {
		r = c_std_syscall(SYS_dup2, ofd, nfd);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
