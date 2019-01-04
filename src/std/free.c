#include <tertium/cpu.h>
#include <tertium/std.h>

#include "alloc.h"

void
c_std_free_(void *p)
{
	pubrealloc(p, 0, " in c_std_free():");
}
