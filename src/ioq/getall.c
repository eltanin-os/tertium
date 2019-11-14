#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_getall(ctype_ioq *p, char *b, usize n)
{
	size r;
	uchar *s;

	s = (uchar *)b;
	while (n) {
		if ((r = c_ioq_get(p, b, n)) < 0)
			return r;
		if (!r)
			break;
		b += r;
		n -= r;
	}

	return s - (uchar *)b;
}
