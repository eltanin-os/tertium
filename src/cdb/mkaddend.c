#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_status
c_cdb_mkaddend(ctype_cdbmk *p, usize klen, usize dlen, u64int h)
{
	struct hp hp;
	usize newoff;

	hp.h = (u32int)h;
	hp.p = p->off;
	if (c_dyn_cat(&p->hplist, &hp, 1, sizeof(hp)) < 0)
		return -1;

	newoff = 8;
	if (C_OFLW_UA(usize, newoff, klen)) {
		errno = C_ENOMEM;
		return -1;
	}
	newoff += dlen;
	if (C_OFLW_UA(usize, newoff, dlen)) {
		errno = C_ENOMEM;
		return -1;
	}
	newoff += klen;
	if (C_OFLW_UA(u32int, p->off, newoff)) {
		errno = C_ENOMEM;
		return -1;
	}
	p->off += newoff;
	return 0;
}
