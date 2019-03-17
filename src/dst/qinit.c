#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_dst_qinit(CQueue *p, CArr *b)
{
	p->mb = b;
	p->os = p->oe = 0;
}
