#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_init(ctype_cdb *p, ctype_fd fd)
{
	ctype_stat st;
	uchar *x;

	p->map = nil;
	c_cdb_free(p);
	c_cdb_findstart(p);
	p->fd = fd;
	if (c_nix_fdstat(&st, fd) < 0)
		return -1;
	if (st.size >= 0xFFFFFFFF) {
		errno = C_ERR_EOVERFLOW;
		return -1;
	}
	if (!(x = c_nix_mmap(0, st.size, C_NIX_PROTREAD, C_NIX_MAPSHARED, fd, 0))) {
		p->size = st.size;
		p->map = x;
	}
	return 0;
}
