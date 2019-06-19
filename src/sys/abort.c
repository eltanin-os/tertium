#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_sys_abort(void)
{
	while (*(volatile int *)0) ;
}
