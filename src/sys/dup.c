#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_dup(int o, int n)
{
	int r;

	do {
		r = c_sys_call(SYS_dup2, o, n);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
