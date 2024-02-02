#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

int
c_tai_leapsub(ctype_tai *p)
{
	u64 u;
	int i, s;

	u = p->x;
	s = 0;
	for (i = 0; i < _tertium_tai_leaptabsize; ++i) {
		if (u < _tertium_tai_leaptab[i])
			break;
		++s;
		if (u == _tertium_tai_leaptab[i]) {
			p->x = u - s;
			return 1;
		}
	}
	p->x = u - s;
	return 0;
}
