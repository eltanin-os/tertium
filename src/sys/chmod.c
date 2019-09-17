#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_chmod(char *s, uint mode)
{
	int r;

	do {
		r = c_sys_call(SYS_chmod, s, mode);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
