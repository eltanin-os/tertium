#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_ioq_peek(CIoq *p)
{
	return (p->mb->p + p->mb->a);
}
