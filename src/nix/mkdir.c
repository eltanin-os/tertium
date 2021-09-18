#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_mkdir(char *s, uint mode)
{
	return c_sys_mkdir(s, mode);
}
