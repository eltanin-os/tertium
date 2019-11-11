#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_init(ctype_ioq *p, ctype_fd fd, ctype_arr *b, ctype_iofn f)
{
	p->mb = b;
	p->op = f;
	p->fd = fd;
	p->opts = 0;
}
