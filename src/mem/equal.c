#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_mem_equal(void *v1, usize n, void *v2)
{
	uint r;
	uchar *s1, *s2;

	s1 = v1;
	s2 = v2;

	r = 0;

	for (; n; n--)
		r |= *s1++ ^ *s2++;

	return r;
}
