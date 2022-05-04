#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_read(ctype_cdb *p, char *s, usize n, ctype_fssize off)
{
	if (p->map) {
		if ((off > p->size) || (p->size - off < (ctype_fssize)n)) {
			errno = C_ERR_EPROTO;
			return -1;
		}
		c_mem_cpy(s, n, p->map + off);
		return 0;
	}
	if (c_nix_seek(p->fd, off, C_NIX_SEEKSET) < 0) return -1;
	if (c_nix_allrw(&c_nix_fdread, p->fd, s, n) < 0) return -1;
	return 0;
}
