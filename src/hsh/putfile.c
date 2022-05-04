#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_hsh_putfile(ctype_hst *hs, ctype_hmd *p, char *s)
{
	ctype_stat st;
	ctype_fd fd;
	ctype_status r;

	if (!c_mem_cmp(s, sizeof("<stdin>") - 1, "<stdin>"))
		return c_hsh_putfd(hs, p, C_IOQ_FD0, 0);

	if ((fd = c_nix_fdopen2(s, C_NIX_OREAD)) < 0)
		return -1;

	r = 0;
	if (c_nix_fdstat(&st, fd) < 0)
		goto fail;
	if (c_hsh_putfd(hs, p, fd, st.size) < 0)
		goto fail;

	goto done;
fail:
	r = -1;
done:
	c_nix_fdclose(fd);
	return r;
}
