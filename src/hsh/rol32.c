#include <tertium/cpu.h>
#include <tertium/std.h>

u32
c_hsh_rol32(u32 n, int k)
{
	uint mask;
	mask = C_LIM_CHARBIT * sizeof(n) - 1;
	k &= mask;
	return ((n << k) | (n >> (-k & mask)));
}
