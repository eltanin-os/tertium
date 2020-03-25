#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_readlink(char *s, char *buf, usize n)
{
	size r;

	if ((r = c_std_syscall(SYS_readlink, s, buf, n)) < 0)
		return -1;
	if ((usize)r == n) {
		errno = C_ENAMETOOLONG;
		return -1;
	}
	buf[r] = 0;
	return r;
}
