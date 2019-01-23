#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_add(CTai *t, CTai *u, CTai *v)
{
	t->x = u->x + v->x;
}
