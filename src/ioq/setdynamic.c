#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_setdynamic(ctype_ioq *p)
{
	p->opts |= __IOQ_ODYNAMIC;
}
