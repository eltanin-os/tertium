#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_ccpy(void *d, void *s, usize n, int c)
{
	uchar *s1, *s2;

	s1 = d;
	s2 = s;

	if (s1 > s2) {
		for (; n; n--)
			if ((*s1++ = *s2++) == c)
				return s1;
	} else {
		s1 += n-1;
		s2 += n-1;
		for (; n; n--)
			if ((*s1-- = *s2--) == c)
				return s1;
	}

	return nil;
}
