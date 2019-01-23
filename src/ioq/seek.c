#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_seek(CIoq *p, usize n)
{
	p->mb->a += n;
	p->mb->n -= n;
}
