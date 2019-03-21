#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_close(CDir *dir)
{
	c_sys_close(dir->__dir.fd);
	return 0;
}
