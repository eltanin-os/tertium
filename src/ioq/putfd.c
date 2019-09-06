#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) \
c_sys_mmap(0, (b), PROT_READ, MAP_SHARED, (a), 0)

ctype_status
c_ioq_putfd(ctype_ioq *p, ctype_fd fd, usize n)
{
	size r;
	char buf[C_BIOSIZ];
	void *mp;

	if (fd && !n)
		return 0;

	if (!fd || (mp = MMAP(fd, n)) == (void *)-1) {
		while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
			if (c_ioq_nput(p, buf, r) < 0)
				return -1;
		return -(r < 0);
	}

	r = c_ioq_nput(p, (char *)mp, n);
	c_sys_munmap(mp, n);
	return -(r < 0);
}
