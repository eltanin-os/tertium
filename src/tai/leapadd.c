#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

void
c_tai_leapadd(ctype_tai *p, int h)
{
	u64 u;
	int i;

	u = p->x;
	for (i = 0; i < _tertium_tai_leaptabsize; ++i) {
		if (u < _tertium_tai_leaptab[i])
			break;
		if (!h || (u > _tertium_tai_leaptab[i]))
			++u;
	}
	p->x = u;
}
