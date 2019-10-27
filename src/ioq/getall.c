#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_getall(ctype_ioq *p, char *b, usize n)
{
	size r, t;

	t = 0;
	while (n) {
		if ((r = c_ioq_get(p, b, n)) < 0)
			return r;
		if (!r)
			break;
		t += r;
		n -= r;
	}

	return t;
}
