#include <tertium/cpu.h>
#include <tertium/std.h>

u64
c_hsh_rol64(u64 n, int k)
{
	return ((n << k) | (n >> (64 - k)));
}
