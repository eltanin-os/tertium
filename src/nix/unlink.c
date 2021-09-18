#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_unlink(char *s)
{
	return c_sys_unlink(s);
}
