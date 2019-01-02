#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_putfile(Ioq *p, char *s)
{
	Stat st;
	int r, fd;

	r = 0;

	if ((fd = c_sys_open(s, O_RDONLY, 0)) < 0)
		return -1;

	if (c_sys_fstat(&st, fd) < 0)
		goto fail;

	if ((c_ioq_putfd(p, fd, st.st_size)) < 0)
		goto fail;

	goto done;
fail:
	r = -1;
done:
	c_sys_close(fd);
	return r;
}
