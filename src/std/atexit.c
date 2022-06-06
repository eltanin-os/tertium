#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *_tertium_atexit;

ctype_status
c_std_atexit(void (*func)(void))
{
	ctype_node *p;
	p = c_adt_lnew((void *)(uintptr)func, sizeof(func));
	if (c_adt_lpush(&_tertium_atexit, p) < 0) return -1;
	return 0;
}
