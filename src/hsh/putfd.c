#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_hsh_putfd(CH32md *p, int fd, usize n)
{
	CH32st hs;
	size   r;
	char   buf[C_BIOSIZ];
	void  *mp;

	if (!n)
		return 0;

	p->init(&hs);

	if (!fd)
		goto fallback;

	if ((mp = c_sys_mmap(0, n, PROT_READ, MAP_SHARED, fd, 0)) == (void *)-1)
		goto fallback;

	p->update(&hs, (char *)mp, n);

	c_sys_munmap(mp, n);

	goto done;
fallback:
	while ((r = c_sys_read(fd, buf, sizeof(buf))) > 0)
		p->update(&hs, buf, r);

	if (r < 0)
		return 0;
done:
	p->end(&hs);
	return hs.a;
}
