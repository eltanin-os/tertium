#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define FOLLOW(a, b) \
((a) & C_FSLOG) || ((a) & C_FSCOM && !(b))

static int
cmp(void *a, void *b)
{
	return *(uvlong *)a - *(uvlong *)b;
}

static int
hist(CDir *p, ulong dev, ulong ino)
{
	CArr  *hp;
	uvlong k;

	hp = &p->hist;
	k = (dev + ino) * (dev + ino + 1) / 2 + ino;
	if (c_std_bsearch(&k, hp, c_arr_len(hp, sizeof(k)), sizeof(k), cmp))
		return 1;

	/* TODO: free & fallback to brute force */
	if (c_dyn_cat(hp, &k, 1, sizeof(k)) < 0)
		return -1;

	/* TODO: replace with ordered insertion */
	c_std_sort(c_arr_data(hp), c_arr_len(hp, sizeof(k)), sizeof(k), cmp);

	return 0;
}

int
__dir_info(CDir *p, CDent *ep)
{
	CStat *stp;
	CStat  st;
	int  (*statf)(CStat *, char *);

	statf = FOLLOW(p->opts, p->depth) ? c_sys_stat : c_sys_lstat;
	stp = &st;
	if (statf(stp, ep->path))
		return C_FSNS;

	if (C_ISDIR(stp->mode)) {
		if (C_ISDOT(ep->name))
			return C_FSDOT;

		return hist(p, stp->dev, stp->ino) ? C_FSDC : C_FSD;
	}

	if (C_ISLNK(stp->mode))
		return C_FSSL;

	if (C_ISREG(stp->mode))
		return C_FSF;

	return C_FSDEF;
}
