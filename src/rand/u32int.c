#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_rand_u32int(u32int n)
{
	u32int min, x;

	if (n < 2)
		return 0;

	min = -n % n;
	for (;;) {
		c_rand_data((void *)(uintptr)&x, sizeof(x));
		if (x >= min)
			break;
	}
	return x % n;
}
