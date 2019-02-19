#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_dyn_cat(CArr *p, void *v, usize m, usize n)
{
	void *dst;

	if (!c_dyn_alloc(p, m, n))
		return -1;

	m  *= n;
	dst = p->p + p->n;
	c_mem_cpy(dst, m, v);
	p->n += m;
	p->p[p->n] = 0;

	return m;
}
