#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_lstat(CStat *p, char *s)
{
	if (c_sys_call(SYS_fstatat, AT_FDCWD, s, p, AT_SYMLINK_NOFOLLOW) < 0)
		return -1;

	return 0;
}
