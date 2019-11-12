#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_munmap(void *p, usize n)
{
	return c_std_syscall(SYS_munmap, p, n);
}
