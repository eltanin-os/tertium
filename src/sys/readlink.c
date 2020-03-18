#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_readlink(char *s, char *buf, usize n)
{
	buf[n - 1] = 0;
	return c_std_syscall(SYS_readlink, s, buf, n - 1);
}
