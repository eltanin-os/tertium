#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_str_cmp(char *v1, usize n, char *v2)
{
	uchar *s1;
	uchar *s2;

	s1 = (uchar *)v1;
	s2 = (uchar *)v2;

	for (; n && *s1 && *s1 == *s2; n--, s1++, s2++)
		;

	return *s1 - *s2;
}
