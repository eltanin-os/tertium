#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_putfd(CIoq *p, int fd, usize n)
{
	size  r;
	char  buf[C_BIOSIZ];
	void *mp;

	if (!fd)
		goto fallback;

	if (!n)
		return 0;

	if ((mp = c_sys_mmap(0, n, PROT_READ, MAP_SHARED, fd, 0)) == (void *)-1)
		goto fallback;

	if (c_ioq_nput(p, (char *)mp, n) < 0)
		return -1;

	c_sys_munmap(mp, n);
	return 0;
fallback:
	while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
		if (c_ioq_nput(p, buf, r) < 0)
			return -1;

	if (r < 0)
		return -1;

	return 0;
}
