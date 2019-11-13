#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_ioq_seek(ctype_ioq *p, usize n)
{
	p->arr.a += n;
	p->arr.n -= n;
}
