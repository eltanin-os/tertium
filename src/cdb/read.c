#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_cdb_read(CCdb *p, char *s, usize n, u32int off)
{
	if (p->map) {
		if ((off > p->size) || (p->size - off < n)) {
			errno = C_EPROTO;
			return -1;
		}
		c_mem_cpy(s, n, p->map + off);
		return 0;
	}

	if (c_sys_seek(p->fd, off, SEEK_SET) < 0)
		return -1;

	if (c_sys_allrw(c_sys_read, p->fd, s, n) < 0)
		return -1;

	return 0;
}
