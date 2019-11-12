#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_sys_open(char *s, uint opts, uint mode)
{
	return c_std_syscall(SYS_open, s, opts, mode);
}
