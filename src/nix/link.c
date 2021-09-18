#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_link(char *newpath, char *oldpath)
{
	return c_sys_link(oldpath, newpath);
}
