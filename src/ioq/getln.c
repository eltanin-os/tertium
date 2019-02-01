#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_getln(CIoq *p, CArr *b)
{
	size  r, n;
	char *s, *nl;

	nl = nil;

	while (!nl) {
		if ((r = c_ioq_feed(p)) <= 0)
			return r;

		s  = c_ioq_peek(p);
		if (!(nl = c_mem_chr(s, r, '\n')))
			n = r;
		else
			n = (nl-s)+1;

		if (c_arr_cat(b, s, n, sizeof(uchar)) < 0)
			return -1;

		c_ioq_seek(p, n);
	}

	return 1;
}
