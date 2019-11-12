#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_std_abort(void)
{
	while (*(volatile int *)0) ;
}
