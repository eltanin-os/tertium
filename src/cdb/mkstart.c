#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_mkstart(ctype_cdbmk *p, ctype_fd fd)
{
	p->fd = fd;
	p->off = 2048;

	c_mem_set(&p->hplist, sizeof(p->hplist), 0);
	c_ioq_init(&p->ioq, fd, p->buf, sizeof(p->buf), c_sys_write);

	if (c_sys_seek(fd, p->off, SEEK_SET) < 0)
		return -1;

	return 0;
}
