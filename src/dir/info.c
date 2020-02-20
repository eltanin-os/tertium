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
		sp[0] = k;
		return 1;
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

	if (*p < k)
		++p;

	c_mem_cpy(p + 1, (uchar *)l - (uchar *)p, p);
	*p = k;
	return 1;
}

static int
hist(ctype_arr *hp, ulong dev, ulong ino)
{
	uvlong k;
	usize n;
	int r;

	n = c_arr_len(hp, sizeof(k));
	if (c_dyn_ready(hp, n + 1, sizeof(k)) < 0)
		return -1;

	k = PACK(dev, ino);
	r = insert(c_arr_data(hp), n, k);
	hp->n += r * sizeof(k);
	return r;
}

static int
dohist(ctype_dir *p, ctype_stat *stp, ushort c1, ushort c2)
{
	switch (hist(&p->hist, stp->dev, stp->ino)) {
	case -1:
		p->opts |= C_FSSTP;
		return C_FSERR;
	case 0:
		return c1;
	default:
		return c2;
	}
}

int
__dir_info(ctype_dir *p, ctype_dent *ep)
{
	ctype_stat *stp;
	ctype_stat st;
	int sverr;

	stp = (p->opts & C_FSNOI) ? &st : ep->stp;
	if (FOLLOW(p->opts, ep->depth)) {
		if (c_sys_stat(ep->path, stp) < 0) {
			sverr = errno;
			if (!c_sys_lstat(ep->path, stp))
				return C_FSSLN;
			ep->err = sverr;
			return C_FSNS;
		}
	} else if (c_sys_lstat(ep->path, stp) < 0) {
		ep->err = errno;
		return C_FSNS;
	}

	if (C_ISDIR(stp->mode)) {
		ep->dev = stp->dev;

		if (C_ISDOT(ep->name))
			return C_FSDOT;

		if (FOLLOW(p->opts, ep->depth))
			return dohist(p, stp, C_FSDC, C_FSD);
		return C_FSD;
	}

	if (C_ISLNK(stp->mode))
		return C_FSSL;

	if (C_ISREG(stp->mode)) {
		if ((p->opts & C_FSFHT) && stp->nlink > 1)
			dohist(p, stp, C_FSFC, C_FSF);
		return C_FSF;
	}

	return C_FSDEF;
}
