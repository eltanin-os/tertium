#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_ioq_peek(Ioq *p)
{
	return (p->mb->p + p->mb->a);
}
