#include <tertium/cpu.h>
#include <tertium/std.h>

u32
c_hsh_rol32(u32 n, int k)
{
	return ((n << k) | (n >> (32 - k)));
}