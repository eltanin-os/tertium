#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_rmdir(char *s)
{
	return c_sys_rmdir(s);
}
