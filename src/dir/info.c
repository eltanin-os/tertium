#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

#define FOLLOW(a, b) ((a) & C_DIR_FSLOG) || ((a) & C_DIR_FSCOM && !(b))
#define PAIR(a, b) ((((a) + (b)) * ((a) + (b) + 1) >> 1) + (b))

struct hp {
	ctype_id h;
	ctype_id p;
};

static int
cmp(void *a, void *b)
{
	uvlong x, y;
	x = *(uvlong *)a;
	y = *(uvlong *)b;
	return ((x > y) - (x < y));
}

static int
hist(ctype_arr *hp, ctype_id dev, ctype_id ino)
{
	uvlong k;
	uvlong *p;
	usize n;
	uchar *s;

	if (c_dyn_ready(hp, 1, sizeof(*p)) < 0) return -1;

	n = c_arr_len(hp, sizeof(*p));
	s = c_arr_data(hp);
	k = PAIR(dev, ino); /* !!! */
	if (*(p = c_std_nbsearch(&k, s, n, sizeof(*p), &cmp)) != k) {
		n = (((uchar *)p - s) / sizeof(*p)) + !!n;
		if (c_dyn_idxcat(hp, n, &k, 1, sizeof(k)) < 0) return -1;
		return 1;
	}
	return 0;
}

static int
dohist(ctype_dir *p, ctype_stat *stp, short c1, short c2)
{
	switch (hist(&p->hist, stp->dev, stp->ino)) {
	case -1:
		p->opts |= C_DIR_FSSTP;
		return C_DIR_FSERR;
	case 0:
		return c1;
	default:
		return c2;
	}
}

int
_tertium_dir_info(ctype_dir *p, ctype_dent *ep)
{
	ctype_stat *stp;
	ctype_stat st;
	ctype_error sverr;

	stp = (p->opts & C_DIR_FSNOI) ? &st : ep->stp;
	if (FOLLOW(p->opts, ep->depth)) {
		if (c_nix_stat(stp, ep->path) < 0) {
			sverr = errno;
			if (!c_nix_lstat(stp, ep->path)) return C_DIR_FSSLN;
			ep->err = sverr;
			return C_DIR_FSNS;
		}
	} else if (c_nix_lstat(stp, ep->path) < 0) {
		ep->err = errno;
		return C_DIR_FSNS;
	}

	switch (stp->mode & C_NIX_IFMT) {
	case C_NIX_IFDIR:
		ep->dev = stp->dev;
		if (C_STD_ISDOT(ep->name)) {
			return C_DIR_FSDOT;
		}
		if (FOLLOW(p->opts, ep->depth)) {
			return dohist(p, stp, C_DIR_FSDC, C_DIR_FSD);
		}
		return C_DIR_FSD;
	case C_NIX_IFLNK:
		return C_DIR_FSSL;
	case C_NIX_IFREG:
		if ((p->opts & C_DIR_FSFHT) && stp->nlink > 1) {
			dohist(p, stp, C_DIR_FSFC, C_DIR_FSF);
		}
		return C_DIR_FSF;
	}
	return C_DIR_FSDEF;
}
