#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_alloc(usize m, usize n)
{
	return __allocator(nil, m, n);
}
