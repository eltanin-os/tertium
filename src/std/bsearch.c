#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_std_bsearch(void *k, void *b, usize n, usize m, int (*f)(void *, void *))
{
	int r;
	uchar *p, *s;

	s = (uchar *)b;

	while (n) {
		p = s + (n >> 1) * m;
		if (!(r = f(k, p))) {
			return p;
		} else if (r > 0) {
			s = p + m;
			n--;
		}
		n >>= 1;
	}

	return nil;
}
