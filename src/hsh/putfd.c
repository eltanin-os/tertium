#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) c_sys_mmap(0, (b), PROT_READ, MAP_SHARED, (a), 0)

ctype_status
bread(ctype_hst *hs, ctype_hmd *p, ctype_fd fd)
{
	size r;
	char buf[C_BIOSIZ];

	while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
		p->update(hs, buf, r);

	return r < 0 ? -1 : 0;
}

ctype_status
c_hsh_putfd(ctype_hst *hs, ctype_hmd *p, ctype_fd fd, usize n)
{
	void *mp;

	if (!n || (mp = MMAP(fd, n)) == (void *)-1)
		return bread(hs, p, fd);
	p->update(hs, (char *)mp, n);
	c_sys_munmap(mp, n);
	return 0;
}
