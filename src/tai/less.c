#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_tai_less(ctype_tai *t, ctype_tai *u)
{
	return t->x < u->x;
}
