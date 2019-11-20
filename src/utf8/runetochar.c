#include <tertium/cpu.h>
#include <tertium/std.h>

extern uchar *__utf8_mtab;

int
c_utf8_runetochar(char *s, ctype_rune *p)
{
	ctype_rune r;
	int i, n;

	r = *p;

	switch ((n = c_utf8_runelen(*p))) {
	case 0:
		return 0;
	case 1:
		s[0] = r;
		return 1;
	}

	for (i = n; i > 1; --i) {
		s[i - 1] = 0x80 | (r & 0x3F);
		r >>= 6;
	}

	s[0] = ~__utf8_mtab[n] | r;

	return n;
}
