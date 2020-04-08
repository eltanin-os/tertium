#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_mem_cmp(void *v1, usize n, void *v2)
{
	uchar *s1, *s2;
	int diff;

	s1 = v1;
	s2 = v2;
	for (; n; --n) {
		if ((diff = *s1 - *s2))
			return diff;
		++s1;
		++s2;
	}
	return 0;

}
