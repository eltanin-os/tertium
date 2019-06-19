#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_close(int f)
{
	int r;

	do {
		r = c_sys_call(SYS_close, f);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
