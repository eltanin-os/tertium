#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_rchr(void *v, usize n, int c)
{
	uchar *s;

	s  = v;
	s += n-1;

	for (; n; n--, s--)
		if (*s == c)
			return s;

	return nil;
}
