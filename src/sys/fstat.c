#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fstat(ctype_fd fd, ctype_stat *p)
{
	if (c_std_syscall(SYS_fstat, fd, p) < 0)
		return -1;

	return 0;
}
