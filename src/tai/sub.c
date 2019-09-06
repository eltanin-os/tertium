#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_sub(ctype_tai *t, ctype_tai *u, ctype_tai *v)
{
	t->x = u->x - v->x;
}
