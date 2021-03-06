#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_chmod(char *s, uint mode)
{
	ctype_status r;

	do {
		r = c_std_syscall(SYS_chmod, s, mode);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
