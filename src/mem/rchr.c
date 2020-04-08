#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_rchr(void *v, usize n, int c)
{
	uchar *s;

	s = (uchar *)v + (n - 1);
	for (; n; --n) {
		if (*s == c)
			return s;
		--s;
	}
	return nil;
}
