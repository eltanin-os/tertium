#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_cat(ctype_arr *p, void *v, usize m, usize n)
{
	if (!m) return 0;
	if (c_dyn_ready(p, m, n) < 0) return -1;
	m *= n;
	c_mem_cpy(p->p + p->n, v, m);
	p->n += m;
	c_mem_set(p->p + p->n, n, 0);
	return 0;
}
