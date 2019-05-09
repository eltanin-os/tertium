#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_calloc(usize m, usize n)
{
	void *p;

	if ((p = __allocator(nil, m, n)))
		c_mem_set(p, n, 0);

	return p;
}
