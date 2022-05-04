#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_nix_fdread(ctype_fd fd, void *p, usize n)
{
	size r;

	do {
		r = c_sys_read(fd, p, n);
	} while ((r < 0) && errno == C_ERR_EINTR);

	return r;
}
