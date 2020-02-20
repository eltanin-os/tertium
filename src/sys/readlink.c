#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_readlink(char *s, char *buf, usize n)
{
	return c_std_syscall(SYS_readlink, s, buf, n);
}
