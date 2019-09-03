#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_mknod(char *s, uint opts, ulong dev)
{
	return c_sys_call(SYS_mknod, s, opts, dev);
}
