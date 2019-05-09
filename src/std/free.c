#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_free_(void *p)
{
	return __allocator(p, 0, sizeof(uchar));
}
