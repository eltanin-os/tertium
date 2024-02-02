#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

void *
c_std_alloc(usize m, usize n)
{
	return _tertium_allocator(nil, m, n);
}
