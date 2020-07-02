#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_caserchr(char *v, usize n, int c)
{
	uchar *s, *p;

	p = nil;
	s = (uchar *)v + (n - 1);
	for (; n && *s; --n) {
		if ((*s | 32) == c)
			p = s;
		--s;
	}
	return (char *)p;
}
