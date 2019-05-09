#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_realloc(void *p, usize m, usize n)
{
	return __allocator(p, m, n);
}
