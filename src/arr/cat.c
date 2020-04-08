#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_cat(ctype_arr *p, void *v, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	if ((m *= n) > c_arr_avail(p)) {
		errno = C_ENOMEM;
		return -1;
	}

	c_mem_cpy(p->p + p->n, m, v);
	p->n += m;
	p->p[p->n] = 0;
	return 0;
}
