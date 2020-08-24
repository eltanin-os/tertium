#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_str_spn(char *v, usize n, char *accept)
{
	uchar *s, *p;

	s = (uchar *)v;
	for (; n && *s; --n) {
		for (p = (uchar *)accept; *p && *s != *p; ++p) ;
		if (!*p)
			break;
		++s;
	}
	return s - (uchar *)v;
}
