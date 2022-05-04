#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_utf8_utfrrune(char *s, ctype_rune r)
{
	ctype_rune rune;
	int n;
	char *p;

	if (r < 0x80)
		return c_str_rchr(s, -1, r);

	p = nil;
	while (*s) {
		n = c_utf8_chartorune(&rune, s);
		if (rune == r)
			p = s;
		s += n;
	}
	return p;
}
