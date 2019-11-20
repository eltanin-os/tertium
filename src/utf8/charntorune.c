#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar tab[] = {
	0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0,
};

extern uchar *__utf8_mtab;

int
c_utf8_charntorune(ctype_rune *p, char *s, usize len)
{
	ctype_rune r;
	usize i, n;

	if (*(uchar *)s <= 0x80) {
		*p = *s;
		return 1;
	}

	if (!(n = C_MIN(len, tab[*s & 0x3F])))
		goto bad;

	if (n > len)
		return 0;

	r = *s & __utf8_mtab[n - 1];

	for (i = 1; i < n; ++i) {
		if ((s[i] ^ 0x80) & 0xC0) {
			len = i;
			goto bad;
		}
		r = (r << 6) | (s[i] & 0x3F);
	}

	if (c_utf8_checkrune(r) < 0)
		goto bad;

	goto done;
bad:
	r = C_RUNEERROR;
done:
	*p = r;
	return len;
}
