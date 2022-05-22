#include <tertium/cpu.h>
#include <tertium/std.h>

u64
c_hsh_ror64(u64 n, int k)
{
	uint mask;
	mask = C_LIM_CHARBIT * sizeof(n) - 1;
	k &= mask;
	return ((n >> k) | (n << (-k & mask)));
}
