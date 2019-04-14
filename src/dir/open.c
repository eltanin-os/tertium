#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_open(CDir *dir, char *path, uint opts)
{
	CStat st;

	if ((dir->fd = c_sys_open(path, C_OREAD|C_OCEXEC, 0)) < 0)
		return -1;

	dir->path = path;
	dir->len  = c_str_len(path, C_USIZEMAX);
	dir->opts = opts;

	if (c_sys_fstat(&st, dir->fd) < 0)
		return -1;

	dir->dev = st.st_dev;

	if (!C_ISDIR(st.st_mode)) {
		errno = C_ENOTDIR;
		return -1;
	}

	return 0;
}
