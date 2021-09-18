#include <tertium/cpu.h>
#include <tertium/std.h>

uint
c_nix_getumask(void)
{
	uint mode;
	c_nix_umask(mode = c_nix_umask(0));
	return mode;
}
