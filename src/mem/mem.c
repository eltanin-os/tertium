#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_mem(void *h, usize hl, void *n, usize nl)
{
	uint i;
	uchar *s;

	if (nl > hl)
		return nil;

	s = h;
	for (i = hl - nl + 1; i; --i) {
		if (!c_mem_cmp(s, nl, n))
			return s;
		++s;
	}
	return nil;
}
