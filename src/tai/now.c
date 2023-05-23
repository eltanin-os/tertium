#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_now(ctype_tai *t)
{
	ctype_time tm;
	c_nix_gettime(&tm);
	c_tai_fromtime(t, &tm);
}
