#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_nix_fdopen2(char *s, uint opts)
{
	return c_sys_open(s, opts, 0);
}
