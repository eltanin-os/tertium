#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) \
c_nix_mmap(0, (b), C_NIX_PROTREAD, C_NIX_MAPSHARED, (a), 0)

static ctype_status
blockread(void *data, ctype_fd fd, ctype_status (*fn)(void *, char *, usize))
{
	ctype_status ret;
	size n;
	char buf[C_IOQ_BSIZ];
	while ((n = c_nix_fdread(fd, buf, sizeof(buf))) > 0) {
		ret = fn(data, buf, n);
		if (ret < 0) return ret;
	}
	if (n < 0) return -100;
	return 0;
}

ctype_status
c_std_putfd(void *data, ctype_fd fd, usize n, ctype_status (*fn)(void *, char *, usize))
{
	ctype_status ret;
	void *mp;
	if (!n || (mp = MMAP(fd, n)) == (void *)-1) {
		return blockread(data, fd, fn);
	}
	ret = fn(data, (char *)mp, n);
	c_nix_munmap(mp, n);
	return ret;
}
