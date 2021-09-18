#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_nix_readlink(char *buf, usize n, char *s)
{
	size r;

	if ((r = c_sys_readlink(s, buf, n)) < 0)
		return -1;
	if ((usize)r == n) {
		errno = C_ENAMETOOLONG;
		return -1;
	}
	buf[r] = 0;
	return r;
}
