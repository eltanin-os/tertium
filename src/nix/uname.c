#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_uname(ctype_utsname *p)
{
	return c_sys_uname(p);
}
