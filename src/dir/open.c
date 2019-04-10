#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_open(CDir *dir, char *path, uint opts)
{
	CArr arr;

	if ((dir->__dir.fd = c_sys_open(path, C_OREAD|C_OCEXEC, 0)) < 0)
		return -1;

	c_arr_init(&arr, dir->path, sizeof(dir->path));
	if (c_arr_cats(&arr, path) < 0)
		return -1;
	if (path[c_arr_bytes(&arr)-1] != '/')
		c_arr_cats(&arr, "/");

	dir->nlen = 0;
	dir->plen = c_arr_bytes(&arr);
	dir->opts = opts;

	if (c_sys_fstat(&dir->info, dir->__dir.fd) < 0)
		return -1;

	dir->dev = dir->info.st_dev;

	if (!C_ISDIR(dir->info.st_mode)) {
		errno = C_ENOTDIR;
		return -1;
	}

	return 0;
}
