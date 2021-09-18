#include <tertium/cpu.h>
#include <tertium/std.h>

uint
c_nix_umask(uint m)
{
	return c_sys_umask(m);
}
