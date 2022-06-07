#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *_tertium_atexit;

ctype_status
c_std_atexit(void (*func)(void))
{
	ctype_node *p;
	if (!(p = c_adt_lnew(nil, 0))) return -1;
	p->p = (void *)(uintptr)func;
	c_adt_lpush(&_tertium_atexit, p);
	return 0;
}
