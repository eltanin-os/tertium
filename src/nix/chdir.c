#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_chdir(char *s)
{
	return c_sys_chdir(s);
}
