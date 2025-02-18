#include <tertium/cpu.h>
#include <tertium/std.h>

#define ROPTS (C_NIX_OREAD|C_NIX_OEXCL)

ctype_fd
c_nix_mktemp5(char *s, usize n, uint opts, uint fdopts, uint fdmode)
{
	return c_nix_mktemp6(s, n, opts, fdopts, fdmode, c_rand_name);
}
