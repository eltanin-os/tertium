#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

int
c_tai_leapsub(ctype_tai *p)
{
	u64int u;
	int i, s;

	u = p->x;
	s = 0;
	for (i = 0; i < __tai_leaptabsize; ++i) {
		if (u < __tai_leaptab[i])
			break;
		++s;
		if (u == __tai_leaptab[i]) {
			p->x = u - s;
			return 1;
		}
	}
	p->x = u - s;
	return 0;
}
