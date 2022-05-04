#include <tertium/cpu.h>
#include <tertium/std.h>

struct hp {
	u32 h;
	u32 p;
};

ctype_status
c_cdb_mkaddend(ctype_cdbmk *p, usize klen, usize dlen, u64 h)
{
	struct hp hp;
	usize newoff;

	hp.h = (u32)h;
	hp.p = p->off;
	if (c_dyn_cat(&p->hplist, &hp, 1, sizeof(hp)) < 0)
		return -1;

	newoff = 8;
	if (C_STD_OVERFLOWA(usize, newoff, klen)) {
		errno = C_ERR_ENOMEM;
		return -1;
	}
	newoff += dlen;
	if (C_STD_OVERFLOWA(usize, newoff, dlen)) {
		errno = C_ERR_ENOMEM;
		return -1;
	}
	newoff += klen;
	if (C_STD_OVERFLOWA(u32, p->off, newoff)) {
		errno = C_ERR_ENOMEM;
		return -1;
	}
	p->off += newoff;
	return 0;
}
