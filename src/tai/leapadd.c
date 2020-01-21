#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

void
c_tai_leapadd(ctype_tai *p, int h)
{
	u64int u;
	int i;

	u = p->x;
	for (i = 0; i < __tai_leaptabsize; ++i) {
		if (u < __tai_leaptab[i])
			break;
		if (!h || (u > __tai_leaptab[i]))
			++u;
	}
	p->x = u;
}
