#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_seek(ctype_ioq *p, usize n)
{
	p->mb->a += n;
	p->mb->n -= n;
}
