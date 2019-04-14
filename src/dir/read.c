#include <tertium/cpu.h>
#include <tertium/std.h>

#define T(a) \
((a) ==  1) ? C_IFIFO : \
((a) ==  2) ? C_IFCHR : \
((a) ==  4) ? C_IFDIR : \
((a) ==  6) ? C_IFBLK : \
((a) ==  8) ? C_IFREG : \
((a) == 10) ? C_IFLNK : \
((a) == 12) ? C_IFSCK : 0

int
c_dir_read(CDent *dent, CDir *dir)
{
	__fb_dirent *d;
	CArr  arr;
	CStat st;
	size  r;
	int (*stf)(CStat *, char *);
	char *sep;
search:
	if (dir->n >= dir->a) {
		if ((r = c_sys_call(__NR_getdents64, dir->fd,
		    dir->buf, sizeof(dir->buf))) < 0)
			return -1;
		if (!r)
			return 0;
		dir->a = r;
		dir->n = 0;
	}

	d = (void *)(dir->buf + dir->n);
	dir->n += d->d_reclen;
	if (C_ISDOT(d->d_name) && (~dir->opts & C_FSDOT))
		goto search;

	c_arr_init(&arr, dent->path, sizeof(dent->path));
	sep = dir->path[dir->len-1] == '/' ? "" : "/";
	if ((r = c_arr_fmt(&arr, "%s%s%s", dir->path, sep, d->d_name)) < 0)
		return -1;

	dent->nlen = c_str_len(d->d_name, C_USIZEMAX);
	dent->plen = r;
	dent->name = dir->path + dent->nlen;

	if (dir->opts & C_FSNOI) {
		c_mem_set(&dent->info, sizeof(dent->info), 0);
		dent->info.st_dev  = dir->dev;
		dent->info.st_ino  = d->d_ino;
		dent->info.st_mode = T(d->d_type);
		if (C_ISLNK(d->d_type) && (dir->opts & C_FSLOG)) {
			if (c_sys_stat(&st, dent->path) < 0)
				return -1;
			dent->info.st_dev  = st.st_dev;
			dent->info.st_ino  = st.st_ino;
			dent->info.st_mode = st.st_mode;
		}
	} else {
		stf = (dir->opts & C_FSLOG) ? c_sys_stat : c_sys_lstat;
		if (stf(&dent->info, dent->path) < 0) {
			c_err_warn("stf %s", dent->path);
			return -1;
		}
	}

	if ((dir->opts & C_FSXDV) && dir->dev != dent->info.st_dev)
		goto search;

	return 1;
}
