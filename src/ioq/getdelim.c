#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_getdelim(ctype_ioq *p, ctype_arr *b, int delim)
{
	size r;
	char *s, *nl;

	nl = nil;
	while (!nl) {
		if ((r = c_ioq_feed(p)) <= 0)
			return r;

		s = c_ioq_peek(p);
		if ((nl = c_mem_chr(s, r, delim)))
			r = (nl - s) + 1;

		if (c_dyn_cat(b, s, r, sizeof(uchar)) < 0)
			return -1;

		c_ioq_seek(p, r);
	}

	return 1;
}
