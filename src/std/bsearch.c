#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_std_bsearch(void *k, void *buf, usize m, usize n, ctype_cmpfn f)
{
	int r;
	uchar *p, *s;
	s = (uchar *)buf;
	while (m) {
		p = s + (m >> 1) * n;
		if (!(r = f(k, p))) {
			return p;
		} else if (r > 0) {
			s = p + n;
			--m;
		}
		m >>= 1;
	}
	return nil;
}
