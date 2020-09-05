#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define FOLLOW(a, b) ((a) & C_FSLOG) || ((a) & C_FSCOM && !(b))
#define PACK(a, b) ((a) << 32 | (b))

static int
cmp(void *a, void *b)
{
	return (*(uvlong *)a - *(uvlong *)b);
}

static int
hist(ctype_arr *hp, ulong dev, ulong ino)
{
	uvlong k;
	uvlong *l, *p;
	usize n;

	if (!(n = c_arr_len(hp, sizeof(k))))
		return c_dyn_cat(hp, &k, 1, sizeof(k)) < 0 ? -1 : 0;
	l = c_arr_data(hp);
	k = PACK(dev, ino);
	if (*l > k) {
		c_dyn_icat(hp, &k, 1, sizeof(k), 0);
		return 1;
	} else if (*(p = c_std_nbsearch(&k, l, n, sizeof(l), &cmp)) != k) {
		c_dyn_icat(hp, &k, 1, sizeof(k), (p + 1) - l);
		return 1;
	}
	return 0;
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
	ctype_error sverr;

	stp = (p->opts & C_FSNOI) ? &st : ep->stp;
	if (FOLLOW(p->opts, ep->depth)) {
		if (c_sys_stat(stp, ep->path) < 0) {
			sverr = errno;
			if (!c_sys_lstat(stp, ep->path))
				return C_FSSLN;
			ep->err = sverr;
			return C_FSNS;
		}
	} else if (c_sys_lstat(stp, ep->path) < 0) {
		ep->err = errno;
		return C_FSNS;
	}

	switch (stp->mode & C_IFMT) {
	case C_IFDIR:
		ep->dev = stp->dev;
		if (C_ISDOT(ep->name))
			return C_FSDOT;
		if (FOLLOW(p->opts, ep->depth))
			return dohist(p, stp, C_FSDC, C_FSD);
		return C_FSD;
	case C_IFLNK:
		return C_FSSL;
	case C_IFREG:
		if ((p->opts & C_FSFHT) && stp->nlink > 1)
			dohist(p, stp, C_FSFC, C_FSF);
		return C_FSF;
	}
	return C_FSDEF;
}
