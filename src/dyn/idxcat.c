#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_idxcat(ctype_arr *p, usize pos, void *v, usize m, usize n)
{
	usize len;
	uchar *target;

	if (c_dyn_ready(p, m, n) < 0) return -1;
	len = c_arr_bytes(p);
	if (!(target = c_dyn_alloc(p, pos, n))) return -1;

	if (pos) pos = (pos - 1) * n;
	m *= n;
	if (len > (pos + n)) {
		c_mem_cpy(target + m, len - pos, target);
		p->n += m;
	} else {
		p->n += m - n;
	}
	c_mem_cpy(target, m, v);
	p->p[p->n] = 0;
	return 0;
}
