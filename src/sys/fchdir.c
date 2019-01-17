#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fchdir(int f)
{
	int r;
	do {
		r = c_sys_call(__NR_fchdir, f);
	} while((r < 0) && (r == EINTR));
	return r;
}
