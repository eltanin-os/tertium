#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_init(ctype_ioq *p, ctype_fd fd, char *buf, usize n, ctype_iofn f)
{
	c_arr_init(&p->arr, buf, n);
	p->op = f;
	p->fd = fd;
	p->opts = 0;
}
