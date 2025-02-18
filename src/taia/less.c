#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_taia_less(ctype_taia *t, ctype_taia *u)
{
	if (t->sec.x != u->sec.x) return t->sec.x < u->sec.x;
	if (t->nano != u->nano) return t->nano < u->nano;
	return t->atto < u->atto;
}
