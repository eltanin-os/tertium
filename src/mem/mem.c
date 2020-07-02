#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_mem(void *h, usize hl, void *n, usize nl)
{
	uchar *p;

	if (nl > hl)
		return nil;

	while ((p = c_mem_chr(h, hl, *(uchar *)n))) {
		if (!c_mem_cmp(p, nl, n))
			break;
		hl -= (p - (uchar *)h) + 1;
		h = p + 1;
	}
	return p;
}
