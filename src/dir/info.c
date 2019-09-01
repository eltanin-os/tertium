#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define FOLLOW(a, b) ((a) & C_FSLOG) || ((a) & C_FSCOM && !(b))
#define PACK(a, b) ((a) << 32 | (b))

static int
insert(uvlong *sp, usize n, uvlong k)
{
	uvlong *p, *l;

	if (!n) {
		sp[0] = 0;
		sp[1] = k;
		return 2;
	}

	l = sp + n;

	while (n) {
		p = sp + (n >> 1);
		if (*p == k) {
			return 0;
		} else if (*p < k) {
			sp = p + 1;
			n--;
		}
		n >>= 1;
	}

	c_mem_cpy(p + 2, (uchar *)l - (uchar *)p, p);
	p[1] = k;

	return 1;
}

static int
hist(CArr *hp, ulong dev, ulong ino)
{
	uvlong k;
	usize n;
	int r;

	n = c_arr_len(hp, sizeof(k));
	if (c_dyn_ready(hp, n+2, sizeof(k)) < 0)
		return -1;

	k = PACK(dev, ino);
	r = insert(c_arr_data(hp), n, k);
	hp->n += r * sizeof(k);

	return r;
}

int
__dir_info(CDir *p, CDent *ep)
{
	CStat *stp;
	CStat  st;
	int    sverr;

	stp = (p->opts & C_FSNOI) ? &st : ep->stp;
	if (FOLLOW(p->opts, ep->depth)) {
		if (c_sys_stat(stp, ep->path) < 0) {
			sverr = errno;
			if (!c_sys_lstat(stp, ep->path))
				return C_FSSLN;
			ep->errno = sverr;
			return C_FSNS;
		}
	} else if (c_sys_lstat(stp, ep->path) < 0) {
		ep->errno = errno;
		return C_FSNS;
	}

	if (C_ISDIR(stp->mode)) {
		ep->dev = stp->dev;

		if (C_ISDOT(ep->name))
			return C_FSDOT;

		switch (hist(&p->hist, stp->dev, stp->ino)) {
		case -1:
			p->opts |= C_FSSTP;
			return C_FSERR;
		case  0:
			return C_FSDC;
		default:
			return C_FSD;
		}
	}

	if (C_ISLNK(stp->mode))
		return C_FSSL;

	if (C_ISREG(stp->mode)) {
		if ((p->opts & C_FSFHT) && stp->nlink > 1)
			switch(hist(&p->hist, stp->dev, stp->ino)) {
			case -1:
				p->opts |= C_FSSTP;
				return C_FSERR;
			case  0:
				return C_FSFC;
			default:
				return C_FSF;
			}
		return C_FSF;
	}

	return C_FSDEF;
}
