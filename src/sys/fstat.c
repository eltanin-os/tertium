#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fstat(ctype_stat *p, ctype_fd fd)
{
	if (c_sys_call(SYS_fstat, fd, p) < 0)
		return -1;

	return 0;
}
