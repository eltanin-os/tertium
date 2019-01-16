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

	i = hl - nl + 1;

	for (; i; i--, s++)
		if (!c_mem_cmp(s, nl, n))
			return s;

	return nil;
}
