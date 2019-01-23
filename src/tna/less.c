#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_tna_less(CTaia *t, CTaia *u)
{
	if (t->sec.x < u->sec.x ||
	    t->nano  < u->nano)
		return 1;
	if (t->sec.x > u->sec.x ||
	    t->nano  > u->nano)
		return 0;
	return t->atto < u->atto;
}
