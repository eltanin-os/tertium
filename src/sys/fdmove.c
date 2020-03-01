#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fdmove(ctype_fd to, ctype_fd from)
{
	if (to == from)
		return 0;
	if (c_sys_fdcopy(to, from) < 0)
		return -1;
	c_sys_close(from);
	return 0;
}
