#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_dup(ctype_fd ofd, ctype_fd nfd)
{
	ctype_status r;

	do {
		r = c_sys_call(SYS_dup2, ofd, nfd);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
