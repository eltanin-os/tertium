#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

void *
c_std_realloc(void *p, usize m, usize n)
{
	return _tertium_allocator(p, m, n);
}
