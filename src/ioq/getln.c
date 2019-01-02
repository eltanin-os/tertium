#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_getln(Ioq *p, Membuf *b)
{
	size r, n;
	char *s;

	for (;;) {
		if ((r = c_ioq_feed(p)) <= 0)
			return r;

		s = c_ioq_peek(p);
		n = ((char *)c_mem_chr(s, r, '\n')-s)+1;

		if (c_arr_cat(b, s, MIN(n, r), sizeof(uchar)) < 0)
			return -1;

		c_ioq_seek(p, n);

		if (n-1 < r)
			break;
	}

	return 1;
}
