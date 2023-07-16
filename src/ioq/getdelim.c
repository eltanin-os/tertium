#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_getdelim(ctype_ioq *p, ctype_arr *b, char *delim)
{
	size n, r;
	int found;
	char *d, *s, *tmp;
	found = 0;
	while (!found) {
		if ((r = n = c_ioq_feed(p)) <= 0) return n;
		s = c_ioq_peek(p);
		for (tmp = delim; *tmp; ++tmp) {
			if ((d = c_mem_chr(s, n, *tmp))) {
				found = 1;
				r = (d - s) + 1;
			}
		}
		if (c_dyn_cat(b, s, r, sizeof(uchar)) < 0) return -1;
		c_ioq_seek(p, r);
	}
	return 1;
}
