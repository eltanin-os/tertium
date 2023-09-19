#include <tertium/cpu.h>
#include <tertium/std.h>

extern ctype_node *_tertium_atexit;

static void
execfunc(void *p)
{
	void (*func)(void);
	*(void **)(&func) = p;
	func();
	c_adt_lfree(p);
}

void
c_std_exit(ctype_status status)
{
	ctype_node *p;

	while ((p = c_adt_lpop(&_tertium_atexit))) execfunc(p->p);

	c_ioq_flush(ioq1);
	c_ioq_flush(ioq2);

	c_sys_exit(status);
}
