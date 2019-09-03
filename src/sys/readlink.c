#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_readlink(char *buf, usize n, char *s)
{
	return c_sys_call(SYS_readlink, s, buf, n);
}
