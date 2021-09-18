#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_stat(ctype_stat *p, char *s)
{
	return c_sys_stat(s, p);
}
