#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_idxcat(ctype_arr *p, usize pos, void *v, usize m, usize n)
{
	usize len;
	uchar *target;

	if (c_dyn_ready(p, m, n) < 0)
		return -1;
	len = c_arr_bytes(p);
	if (!(target = c_dyn_alloc(p, pos, n)))
		return -1;
	p->n = len;
	m *= n;
	if (!pos || (pos = (pos - 1) * n) < len)
		c_mem_cpy(target + m, p->n - pos, target);
	c_mem_cpy(target, m, v);
	p->n += m;
	p->p[p->n] = 0;
	return 0;
}
