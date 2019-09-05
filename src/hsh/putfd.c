#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) \
c_sys_mmap(0, (b), PROT_READ, MAP_SHARED, (a), 0)

int
c_hsh_putfd(CHst *hs, CHmd *p, int fd, usize n)
{
	size r;
	char buf[C_BIOSIZ];
	void *mp;

	if (fd && !n)
		return 0;

	p->init(hs);

	if (!fd || (mp = MMAP(fd, n)) == (void *)-1) {
		while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
			p->update(hs, buf, r);
		p->end(hs);
		return -(r < 0);
	}

	p->update(hs, (char *)mp, n);
	p->end(hs);
	c_sys_munmap(mp, n);
	return 0;
}
