#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_lstat(CStat *p, char *s)
{
	__fb_stat st;

	if (c_sys_call(SYS_fstatat, AT_FDCWD, s, &st, AT_SYMLINK_NOFOLLOW) < 0)
		return -1;

	__C_STCOPY(p, st);

	return 0;
}
