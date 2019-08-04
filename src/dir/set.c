#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_set(CDir *p, CDent *ep, int instr)
{
	(void)p;
	ep->instr = instr;
	return 0;
}
