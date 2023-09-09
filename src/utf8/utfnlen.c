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
		if ((r = c_utf8_charntorune(&rune, s, n)) <= 0) break;
		s += r;
		n -= r;
		++len;
	}
	return len;
}
