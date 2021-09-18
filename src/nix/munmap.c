#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_nix_munmap(void *p, usize n)
{
	int sverr;

	sverr = errno;
	c_sys_munmap(p, n);
	errno = sverr;
}
