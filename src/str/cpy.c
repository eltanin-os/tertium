#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_cpy(char *d, usize n, char *s)
{
	uchar *s1, *s2;

	s1 = (uchar *)d;
	s2 = (uchar *)s;

	if (s == d)
		return (char *)d;

	if (s > d) {
		for (; n; n--)
			if (!(*s1++ = *s2++))
				break;
	} else {
		s1 += n-1;
		s2 += n-1;
		for (; n; n--)
			if (!(*s1-- = *s2--))
				break;
	}

	return (char *)d;
}
