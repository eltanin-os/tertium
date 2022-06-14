#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_nix_mktemp(char *s, usize n)
{
	return c_nix_mktemp3(s, n, 0);
}
