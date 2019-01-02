#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_init(Ioq *p, int fd, Membuf *b, size (*f)(int, void *, usize))
{
	p->mb = b;
	p->op = f;
	p->fd = fd;
}
