#include <tertium/cpu.h>
#include <tertium/std.h>

#define MMAP(a, b) \
c_nix_mmap(0, (b), C_PROT_READ, C_MAP_SHARED, (a), 0)

ctype_status
c_ioq_putfd(ctype_ioq *p, ctype_fd fd, usize n)
{
	ctype_status r;
	void *mp;

	if (!n || (mp = MMAP(fd, n)) == (void *)-1) {
		c_ioq_flush(p);
		return (c_nix_fdcat(c_ioq_fileno(p), fd) < 0);
	}
	r = (c_ioq_nput(p, (char *)mp, n) < 0);
	c_nix_munmap(mp, n);
	return r;
}
