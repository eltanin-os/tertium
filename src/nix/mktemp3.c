#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_nix_mktemp3(char *s, usize n, uint opts)
{
	return c_nix_mktemp4(s, n, opts, 0);
}
