#include <tertium/cpu.h>
#include <tertium/std.h>

#define MODE(x) ((x) & C_NIX_OTMPDIR ? 0700 : 0600)

ctype_fd
c_nix_mktemp4(char *s, usize n, uint opts, uint fdopts)
{
	return c_nix_mktemp5(s, n, opts, fdopts, MODE(opts));
}
