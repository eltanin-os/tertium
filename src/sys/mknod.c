#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_mknod(char *s, uint opts, ctype_fsid dev)
{
	return c_sys_call(SYS_mknod, s, opts, dev);
}
