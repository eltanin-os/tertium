#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_icat(ctype_arr *p, void *v, usize m, usize n, usize pos)
{
	usize len;
	uchar *target;

	len = c_arr_bytes(p);
	if (!(target = c_arr_get(p, pos, n)))
		return -1;
	p->n = len;
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}
	if ((m *= n) > c_arr_avail(p)) {
		errno = C_ENOMEM;
		return -1;
	}
	if (!pos || (pos = (pos - 1) * n) < len)
		c_mem_cpy(target + m, p->n - pos, target);
	c_mem_cpy(target, m, v);
	p->n += m;
	p->p[p->n] = 0;
	return 0;

}
