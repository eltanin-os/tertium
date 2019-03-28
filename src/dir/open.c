#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_open(CDir *dir, char *path, uint opts)
{
	CStat st;

	if ((dir->__dir.fd = c_sys_open(path, C_OREAD|C_OCEXEC, 0)) < 0)
		return -1;

	dir->dir  = path;
	dir->dlen = c_str_len(path);
	dir->opts = opts;

	if (c_sys_fstat(&st, dir->__dir.fd) < 0)
		return -1;

	dir->dev = st.st_dev;

	if (!C_ISDIR(st.st_mode))
		return -1;

	return 0;
}
