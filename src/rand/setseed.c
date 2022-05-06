#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_rand_setseed(ctype_rst *p, u64 seed)
{
	p->state = seed;
}
