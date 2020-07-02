#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_casechr(char *v, usize n, int c)
{
	uchar *s;

	s = (uchar *)v;
	for (; n && *s; --n) {
		if ((*s | 32) == c)
			return (char *)s;
		++s;
	}
	return nil;
}
