#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdmove(ctype_fd to, ctype_fd from)
{
	if (to == from)
		return 0;
	if (c_nix_fdcopy(to, from) < 0)
		return -1;
	c_nix_fdclose(from);
	return 0;
}
