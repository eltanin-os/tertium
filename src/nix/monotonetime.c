#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_nix_monotonetime(ctype_time *t)
{
	int sverr;
	sverr = errno;
	c_sys_clockgettime(C_NIX_CLOCKMONO, t);
	errno = sverr;
}
