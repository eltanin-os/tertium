#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_chr(char *v, usize n, int c)
{
	uchar *s;

	s = (uchar *)v;

	for (; *s && n; n--, s++)
		if (*s == c)
			return (char *)s;

	return nil;
}
