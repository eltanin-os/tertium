#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_symlink(char *path, char *target)
{
	return c_sys_symlink(target, path);
}
