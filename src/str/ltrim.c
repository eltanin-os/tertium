#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_ltrim(char *str, usize n, char *t)
{
	usize tlen;
	uchar *s;
	tlen = c_str_len(t, -1);
	s = (uchar *)str;
	for (; n && *s; --n, ++s) {
		if (!c_mem_chr(t, tlen, *s)) break;
		*s = 0;
	}
	return (char *)s;
}
