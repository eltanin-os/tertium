#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fchdir(int f)
{
	int r;

	do {
		r = c_sys_call(SYS_fchdir, f);
	} while((r < 0) && (errno == EINTR));

	return r;
}
