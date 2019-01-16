#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_tai_less(Tai *t, Tai *u)
{
	return t->x < u->x;
}
