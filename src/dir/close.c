#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_close(CDir *p)
{
	c_dyn_free(&p->hist);
	return 0;
}
