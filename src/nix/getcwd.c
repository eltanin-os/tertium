#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_nix_getcwd(char *s, usize n)
{
	return c_sys_getcwd(s, n);
}
