#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_nix_fdclose(ctype_fd fd)
{
	int sverr;

	sverr = errno;
	c_sys_close(fd);
	errno = sverr;
}
