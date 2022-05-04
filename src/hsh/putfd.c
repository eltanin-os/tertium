#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) c_nix_mmap(0, (b), C_NIX_PROTREAD, C_NIX_MAPSHARED, (a), 0)

static ctype_status
read(ctype_hst *hs, ctype_hmd *p, ctype_fd fd)
{
	size r;
	char buf[C_IOQ_BSIZ];

	while ((r = c_nix_fdread(fd, buf, sizeof(buf))) > 0)
		p->update(hs, buf, r);

	if (r < 0)
		return -1;

	return 0;
}

ctype_status
c_hsh_putfd(ctype_hst *hs, ctype_hmd *p, ctype_fd fd, usize n)
{
	void *mp;

	if (!n || (mp = MMAP(fd, n)) == (void *)-1)
		return read(hs, p, fd);
	p->update(hs, (char *)mp, n);
	c_nix_munmap(mp, n);
	return 0;
}
