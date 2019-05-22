#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_sys_mmap(void *p, usize n, int prot, int o, int fd, int off)
{
	return (void *)(uintptr)c_sys_call(SYS_mmap, p, n, prot, o, fd, off);
}
