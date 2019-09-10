#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_readlink(char *buf, usize n, char *s)
{
	size r;

	if ((r = c_sys_call(SYS_readlink, s, buf, n - 1)) < 0)
		return -1;

	buf[r] = 0;

	return r;
}
