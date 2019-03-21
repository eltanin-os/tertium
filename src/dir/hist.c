#include <tertium/cpu.h>
#include <tertium/std.h>

struct hist {
	ushort dev;
	ushort ino;
};

int
c_dir_hist(CStat *st, CNode **hist)
{
	struct hist h;
	CNode *np;

	h.dev = st->st_dev;
	h.ino = st->st_ino;

	np = *hist;
	for (;;) {
		if (((struct hist *)(np->p))->dev == h.dev &&
		    ((struct hist *)(np->p))->ino == h.ino)
			return 1;
		if ((np = np->next) == *hist)
			break;
	}

	if (c_dst_lpush(hist, c_dst_lnew(&h, 1, sizeof(h))) < 0)
		return -1;

	return 0;
}
