#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_open(CDir *dir, char *path, uint opts)
{
	CStat st;

	c_mem_set(dir, sizeof(*dir), 0);
	if ((dir->__dir.fd = c_sys_open(path, C_OREAD|C_OCEXEC, 0)) < 0)
		return -1;

	dir->dir  = path;
	dir->dlen = c_str_len(path);

	if (c_sys_fstat(&st, dir->__dir.fd) < 0)
		return -1;

	if (!C_ISDIR(st.st_mode))
		return -1;

	return 0;
}
