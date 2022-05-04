#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_mkstart(ctype_cdbmk *p, ctype_fd fd)
{
	p->fd = fd;
	p->off = 2048;
	c_mem_set(&p->hplist, sizeof(p->hplist), 0);
	c_ioq_init(&p->ioq, fd, p->buf, sizeof(p->buf), c_nix_fdwrite);
	if (c_nix_seek(fd, p->off, C_NIX_SEEKSET) < 0) return -1;
	return 0;
}
