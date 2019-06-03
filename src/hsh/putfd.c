#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_hsh_putfd(CHst *hs, CHmd *p, int fd, usize n)
{
	size  r;
	char  buf[C_BIOSIZ];
	void *mp;

	if (!fd)
		goto fallback;

	if (!n)
		return 0;

	p->init(hs);

	if ((mp = c_sys_mmap(0, n, PROT_READ, MAP_SHARED, fd, 0)) == (void *)-1)
		goto fallback;

	p->update(hs, (char *)mp, n);
	c_sys_munmap(mp, n);

	goto done;
fallback:
	while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
		p->update(hs, buf, r);

	if (r < 0)
		return -1;
done:
	p->end(hs);
	return 0;
}
