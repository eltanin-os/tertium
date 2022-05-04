#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

void *
c_std_calloc(usize m, usize n)
{
	void *p;

	if ((p = _tertium_allocator(nil, m, n)))
		c_mem_set(p, n, 0);

	return p;
}
