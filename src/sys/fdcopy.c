#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fdcopy(ctype_fd to, ctype_fd from)
{
	if (to == from)
		return 0;
	return c_sys_dup2(from, to);
}
