#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_lstat(ctype_stat *p, char *s)
{
	if (c_sys_call(SYS_fstatat, AT_FDCWD, s, p, AT_SYMLINK_NOFOLLOW) < 0)
		return -1;

	return 0;
}
