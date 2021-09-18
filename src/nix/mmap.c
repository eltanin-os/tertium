#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_nix_mmap(void *p, usize n, int prot, uint opts, ctype_fd fd, ctype_fssize off)
{
	return c_sys_mmap(p, n, prot, opts, fd, off);
}
