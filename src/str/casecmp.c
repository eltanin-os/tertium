#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_str_casecmp(char *v1, usize n, char *v2)
{
	uchar *s1, *s2;
	int diff;

	s1 = (uchar *)v1;
	s2 = (uchar *)v2;
	for (; n; --n) {
		if ((diff = (*s1 | 32) - (*s2 | 32)))
			return diff;
		if (!*s1)
			return 0;
		++s1;
		++s2;
	}
	return 0;
}
