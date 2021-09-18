#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_lstat(ctype_stat *p, char *s)
{
	return c_sys_lstat(s, p);
}
