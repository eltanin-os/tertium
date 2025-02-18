#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_taia_add(ctype_taia *t, ctype_taia *u, ctype_taia *v)
{
	t->sec.x = u->sec.x + v->sec.x;
	t->nano = u->nano + v->nano;
	t->atto = u->atto + v->atto;

	if (t->atto > 999999999UL) {
		t->atto -= 1000000000UL;
		t->nano++;
	}

	if (t->nano > 999999999UL) {
		t->nano -= 1000000000UL;
		t->sec.x++;
	}
}
