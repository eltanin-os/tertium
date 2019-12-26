#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_read(ctype_cdb *p, char *s, usize n, u32int off)
{
	if (p->map) {
		if ((off > p->size) || (p->size - off < n)) {
			errno = C_EPROTO;
			return -1;
		}
		c_mem_cpy(s, n, p->map + off);
		return 0;
	}

	if (c_sys_seek(p->fd, off, C_SEEKSET) < 0)
		return -1;

	if (c_std_allrw(c_sys_read, p->fd, s, n) < 0)
		return -1;

	return 0;
}
