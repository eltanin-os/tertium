#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

ctype_allocfn _tertium_allocator = pubrealloc;

void
c_std_setalloc(ctype_allocfn f)
{
	_tertium_allocator = f ? f : pubrealloc;
}
