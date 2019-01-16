#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_add(Tai *t, Tai *u, Tai *v)
{
	t->x = u->x + v->x;
}
