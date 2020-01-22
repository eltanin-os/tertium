#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_fd
c_ioq_fileno(ctype_ioq *p)
{
	return p->fd;
}
