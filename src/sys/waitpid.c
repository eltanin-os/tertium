#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_sys_waitpid(ctype_id id, int *status, uint opts)
{
	return c_sys_call(SYS_waitpid, id, status, opts);
}
