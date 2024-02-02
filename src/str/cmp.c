#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_str_cmp(char *l, usize n, char *r)
{
	uchar *a, *b;
	int diff;

	a = (uchar *)l;
	b = (uchar *)r;
	for (; n; ++a, ++b, --n) {
		if ((diff = *a - *b)) return diff;
		if (!*a) break;
	}
	return 0;
}
