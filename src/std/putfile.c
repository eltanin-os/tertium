#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_std_putfile(void *data, char *s, ctype_status (*fn)(void *, char *, usize))
{
	ctype_stat st;
	ctype_fd fd;
	ctype_status r;

	if (!c_mem_cmp(s, sizeof("<stdin>") - 1, "<stdin>")) {
		return c_std_putfd(data, C_IOQ_FD0, 0, fn);
	}

	if ((fd = c_nix_fdopen2(s, C_NIX_OREAD)) < 0) return -1;
	if (c_nix_fdstat(&st, fd) < 0) {
		c_nix_fdclose(fd);
		return -1;
	}
	r = c_std_putfd(data, fd, st.size, fn);
	c_nix_fdclose(fd);
	return r;
}
