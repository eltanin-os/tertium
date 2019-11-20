#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_utf8_utfnlen(char *s, usize n)
{
	ctype_rune rune;
	usize len;
	int r;

	len = 0;
	while (*s) {
		r = c_utf8_charntorune(&rune, s, n);
		s += r;
		n -= r;
		++len;
	}
	return len;
}
