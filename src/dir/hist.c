#include <tertium/cpu.h>
#include <tertium/std.h>

struct hist {
	ushort dev;
	ushort ino;
};

int
c_dir_hist(CStat *st, CNode **hist)
{
	struct hist *hp;
	struct hist  h;
	CNode *np;

	h.dev = st->st_dev;
	h.ino = st->st_ino;

	if ((np = *hist))
		for (;;) {
			np = np->next;
			hp = np->p;
			if (hp->dev == h.dev && hp->ino == h.ino)
				return 1;
			if (np == *hist)
				break;
		}

	if (c_dst_lpush(hist, c_dst_lnew(&h, 1, sizeof(h))) < 0)
		return -1;

	return 0;
}
