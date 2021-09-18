#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_rename(char *d, char *s)
{
	return c_sys_rename(s, d);
}
