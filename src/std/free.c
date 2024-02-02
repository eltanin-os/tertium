#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

void *
c_std_free_(void *p)
{
	return _tertium_allocator(p, 0, sizeof(uchar));
}
