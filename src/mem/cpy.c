#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_cpy(void *d, usize n, void *s)
{
	uchar *s1, *s2;

	s1 = d;
	s2 = s;

	if (s1 == s2)
		return d;

	if (s1 > s2) {
		for (; n; n--)
			*s1++ = *s2++;
	} else {
		s1 += n-1;
		s2 += n-1;
		for (; n; n--)
			*s1-- = *s2--;
	}

	return d;
}
