#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_str(char *h, usize n, char *s)
{
	usize len;
	char *p;

	len = c_str_len(s, -1);
	if (len > n)
		return nil;

	while ((p = c_str_chr(h, n, *s))) {
		if (!c_str_cmp(p, len, s))
			break;
		n -= (p - h) + 1;
		h = p + 1;
	}
	return p;
}
