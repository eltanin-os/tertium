#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_cchr(void *v, usize n, int c1, int c2)
{
	uchar *s;

	s = v;

	for (; n; n--, s++) {
		if (*s == c1)
			return s;
		if (*s == c2)
			break;
	}

	return nil;
}
