#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
event(void *data, char *s, usize n)
{
	ctype_fd *fd;
	fd = data;
	return -(c_nix_allrw(c_nix_fdwrite, *fd, s, n) < 0);
}

ctype_status
c_nix_fdputfd(ctype_fd dest, ctype_fd src, usize n)
{
	return c_std_putfd(&dest, src, n, &event);
}

ctype_status
c_nix_fdputfile(ctype_fd fd, char *s)
{
	return c_std_putfile(&fd, s, &event);
}
