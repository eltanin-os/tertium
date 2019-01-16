#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_mem_cmp(void *v1, usize n, void *v2)
{
	uchar *s1, *s2;

	s1 = v1;
	s2 = v2;

	for (; n && *s1 == *s2; n--, s1++, s2++)
		;

	return n ? s1 - s2 : 0;
}
