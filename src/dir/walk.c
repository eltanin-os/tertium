#include <tertium/cpu.h>
#include <tertium/std.h>

typedef struct {
	CDent *dp;
	CNode *hp;
	int    depth;
	int    maxdepth;
	uint   opts;
} Dir;

static int
walk(Dir *p, char *s, void *v, int (*f)(CDent *, void *))
{
	CDir  dir;
	CDent dent;
	int   r;

	if (!(p->hp == (void *)-1) &&
	    (r = c_dir_hist(&p->hp, &p->dp->info)))
		return r;

	if (c_dir_open(&dir, s, p->opts) < 0)
		return -1;

	if (!(p->opts & C_FSDRL)) {
		if (f(p->dp, v) < 0)
			return -1;
	} else {
		c_mem_cpy(&dent, sizeof(dent), p->dp);
	}

	p->depth++;
	while ((r = c_dir_read(p->dp, &dir)) > 0) {
		if (C_ISDIR(p->dp->info.st_mode) &&
		    (!p->maxdepth || p->depth < p->maxdepth)) {
			if (walk(p, p->dp->path, v, f) < 0)
				return -1;
		} else {
			if (f(p->dp, v) < 0)
				return -1;
		}
	}
	p->depth--;

	c_dir_close(&dir);

	if (p->opts & C_FSDRL) {
		c_mem_cpy(p->dp, sizeof(*p->dp), &dent);
		if (f(p->dp, v) < 0)
			return -1;
	}

	return r;
}

int
c_dir_walk(char **pv, int mxd, uint opts, void *v, int (*f)(CDent *, void *))
{
	CDent dent;
	Dir   dir;
	int (*statf)(CStat *, char *);
	int   r;
	char *s;

	c_mem_set(&dir, sizeof(dir), 0);

	if (C_FSFLW(opts, 0)) {
		statf = c_sys_stat;
	} else {
		statf = c_sys_lstat;
		dir.hp = (void *)-1;
	}

	dir.dp = &dent;
	dir.maxdepth = mxd;
	dir.opts = opts;

	for (; *pv; pv++) {
		s = *pv;

		dent.plen = c_str_len(s, C_USIZEMAX);
		dent.nlen = 0;
		c_mem_cpy(dent.path, dent.plen, s);

		if ((r = statf(&dent.info, s)) < 0)
			break;

		if (!C_ISDIR(dent.info.st_mode) &&
		    (r = f(&dent, v)) < 0)
			break;

		if ((r = walk(&dir, s, v, f)) < 0)
			break;

		if ((opts & C_FSKHP) || (dir.hp == (void *)-1))
			continue;

		while (dir.hp)
			c_adt_lfree(c_adt_lpop(&dir.hp));
	}

	if (!(dir.hp == (void *)-1))
		while (dir.hp)
			c_adt_lfree(c_adt_lpop(&dir.hp));

	return r;
}
