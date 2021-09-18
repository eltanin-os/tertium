#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_nix_gettime(ctype_time *t)
{
	int sverr;

	sverr = errno;
	c_sys_clockgettime(C_CLOCK_REALTIME, t);
	errno = sverr;
}
