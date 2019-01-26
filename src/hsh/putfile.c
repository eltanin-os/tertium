#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_hsh_putfile(CH32md *p, char *s)
{
	CStat  st;
	int    fd;
	u32int r;

	if ((fd = c_sys_open(s, C_OREAD, 0)) < 0)
		return 0;

	if (c_sys_fstat(&st, fd) < 0)
		goto fail;

	r = c_hsh_putfd(p, fd, st.st_size);

	goto done;
fail:
	r = 0;
done:
	c_sys_close(fd);
	return r;
}
