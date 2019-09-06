#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_allocfn __allocator = pubrealloc;

void
c_std_setalloc(ctype_allocfn f)
{
	__allocator = f ? f : pubrealloc;
}
