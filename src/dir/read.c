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
c_dir_read(CDir *dir)
{
	__fb_dirent *d;
	CArr  arr;
	CStat st;
	size  r;
	int (*stf)(CStat *, char *);
search:
	if (dir->__dir.os >= dir->__dir.oe) {
		if ((r = c_sys_call(__NR_getdents64, dir->__dir.fd,
		    dir->__dir.buf, sizeof(dir->__dir.buf))) < 0)
			return -1;
		if (!r)
			return 0;
		dir->__dir.oe = r;
		dir->__dir.os = 0;
	}

	d = (void *)(dir->__dir.buf + dir->__dir.os);
	dir->__dir.os += d->d_reclen;
	if (C_ISDOT(d->d_name) &&
	    (~dir->opts & C_FSDOT))
		goto search;

	c_arr_init(&arr, dir->path, sizeof(dir->path));
	if (c_arr_fmt(&arr, "%s/%s", dir->dir, d->d_name) < 0)
		return -1;

	dir->name = dir->path + dir->dlen + 1;
	dir->nlen = c_str_len(dir->name);
	dir->plen = c_arr_bytes(&arr);

	if (dir->opts & C_FSNOI) {
		c_mem_set(&dir->info, sizeof(dir->info), 0);
		dir->info.st_dev  = dir->dev;
		dir->info.st_ino  = d->d_ino;
		dir->info.st_mode = T(d->d_type);
		if (C_ISLNK(d->d_type) && C_FSFLW(dir->opts, dir->depth)) {
			if (c_sys_stat(&st, dir->path) < 0)
				return -1;
			dir->info.st_dev  = st.st_dev;
			dir->info.st_ino  = st.st_ino;
			dir->info.st_mode = st.st_mode;
		}
	} else {
		stf = C_FSFLW(dir->opts, dir->depth) ? c_sys_stat : c_sys_lstat;
		if (stf(&dir->info, dir->path) < 0)
			return -1;
	}

	if ((dir->opts & C_FSXDV) &&
	    dir->dev != dir->info.st_dev)
		goto search;

	return 1;
}
