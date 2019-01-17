#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_close(int f)
{
	int r;
	do {
		r = c_sys_call(__NR_close, f);
	} while ((r < 0) && (r == EINTR));
	return r;
}
