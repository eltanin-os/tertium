#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_chr(void *v, usize n, int c)
{
	uchar *s;

	s = v;

	for (; n; n--, s++)
		if (*s == c)
			return s;

	return nil;
}
