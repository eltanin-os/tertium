#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

void * (*__allocator)(void *, usize, usize) = pubrealloc;

void
c_std_setalloc(void *(*f)(void *, usize, usize))
{
	__allocator = f;
}
