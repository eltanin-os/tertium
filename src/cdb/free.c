#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_cdb_free(CCdb *p)
{
	if (p->map)
		c_sys_munmap(p->map, p->size);

	c_mem_set(p, sizeof(*p), 0);
	p->fd = -1;
}
