#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_rchr(char *v, usize n, int c)
{
	uchar *p, *s;

	p = nil;
	s = (uchar *)v;
	for (; n && *s; --n) {
		if (*s == c)
			p = s;
		++s;
	}
	return (char *)p;
}
