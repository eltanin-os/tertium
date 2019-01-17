#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_dup(int o, int n)
{
	int r;
	do {
		r = c_sys_call(__NR_dup2, o, n);
	} while ((r < 0) && (r == EINTR));
	return r;
}
