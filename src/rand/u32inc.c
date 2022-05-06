#include <tertium/cpu.h>
#include <tertium/std.h>

u32
c_rand_u32inc(ctype_rst *p, u32 n)
{
	u32 min, x;

	if (n < 2)
		return 0;

	min = -n % n;
	for (;;) {
		c_rand_datainc(p, (void *)(uintptr)&x, sizeof(x));
		if (x >= min) break;
	}
	return x % n;
}
