#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void *
c_std_realloc(void *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_ENOMEM;
		return nil;
	}

	return pubrealloc(p, m*n);
}
