#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_nix_fdopen3(char *s, uint opts, uint mode)
{
	return c_sys_open(s, opts, mode);
}
