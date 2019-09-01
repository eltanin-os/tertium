#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dir_close(CDir *p)
{
	while (p->cur)
		c_adt_lfree(c_adt_lpop(&p->cur));

	c_dyn_free(&p->hist);

	return 0;
}
