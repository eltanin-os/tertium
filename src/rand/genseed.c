#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_rand_genseed(ctype_rst *p)
{
	c_rand_data((void *)(uintptr)&p->state, sizeof(p->state));
}
