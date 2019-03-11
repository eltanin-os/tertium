#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_alloc(usize m, usize n)
{
	if (C_OFLW_UM(usize, n, m))
		return nil;

	return pubrealloc(nil, m*n);
}
