#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_alloc(usize m, usize n)
{
	if (n && m > (usize)-1/n)
		return nil;

	return pubrealloc(nil, m*n, " in c_std_alloc():");
}
