#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

u32int
__hsh_rol32(u32int n, int k)
{
	return ((n << k) | (n >> (32 - k)));
}

u32int
__hsh_ror32(u32int n, int k)
{
	return ((n >> k) | (n << (32 - k)));
}

u64int
__hsh_ror64(u64int n, int k)
{
	return ((n >> k) | (n << (64 - k)));
}
