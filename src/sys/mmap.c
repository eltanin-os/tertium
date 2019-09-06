#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_sys_mmap(void *p, usize n, int prot, uint opts, ctype_fd fd, ctype_fssize off)
{
	return (void *)(uintptr)c_sys_call(SYS_mmap, p, n, prot, opts, fd, off);
}
