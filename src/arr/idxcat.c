#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_idxcat(ctype_arr *p, usize pos, void *v, usize m, usize n)
{
	usize len;
	uchar *target;

	if (c_arr_ready(p, m, n) < 0)
		return -1;

	len = c_arr_bytes(p);
	if (!(target = c_arr_get(p, pos, n)))
		return -1;
	p->n ^= len;
	len ^= p->n;
	p->n ^= len;

	m *= n;
	if (pos) pos = (pos - 1) * n;
	c_mem_cpy(target + m, c_arr_bytes(p) - pos, target);
	c_mem_cpy(target, m, v);
	p->n = (p->n == len) ? p->n + m : len;
	p->p[p->n] = 0;
	return 0;

}
