#include <tertium/cpu.h>
#include <tertium/std.h>

#include "cdb.h"

int
c_cdb_mkaddend(CCdbmk *p, usize klen, usize dlen, u32int h)
{
	struct hp hp;
	vlong newoff;

	hp.h = h;
	hp.p = p->off;
	if (c_dyn_cat(&p->hplist, &hp, 1, sizeof(hp)) < 0)
		return -1;

	newoff = dlen + klen + 8;

	if (C_OFLW_UA(u32int, p->off, newoff)) {
		errno = C_ENOMEM;
		return -1;
	}

	p->off += newoff;

	return 0;
}
