#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_utf8_utfrune(char *s, ctype_rune r)
{
	ctype_rune rune;
	int n;

	if (r < 0x80)
		return c_str_chr(s, C_USIZEMAX, r);

	while (*s) {
		n = c_utf8_chartorune(&rune, s);
		if (rune == r)
			return s;
		s += n;
	}
	return nil;
}
