#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_calloc(usize m, usize n)
{
	void *p;

	if (n && m > (usize)-1/n)
		return nil;

	if ((p = pubrealloc(nil, m*n, " in c_std_calloc():")))
		c_mem_set(p, n, 0);

	return p;
}
