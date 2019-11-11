#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_setnoflush(ctype_ioq *p)
{
	p->opts |= __IOQ_ONOFLUSH;
}
