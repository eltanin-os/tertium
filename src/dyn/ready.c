#include <tertium/cpu.h>
#include <tertium/std.h>

#define GFACT 1.618

ctype_status
c_dyn_ready(ctype_arr *p, usize m, usize n)
{
	usize a;
	void *tmp;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	m = (m * n) + n;
	if (p->a) {
		if (m > c_arr_avail(p)) {
			a = p->a;
			while (m > (a - p->n)) a *= GFACT;
			if (!(tmp = c_std_realloc(p->p, a, sizeof(uchar))))
				return -1;
			p->p = tmp;
			p->a = a;
		}
	} else {
		if (!(p->p = c_std_alloc((p->a = m * GFACT), sizeof(uchar))))
			return -1;
	}
	return 0;
}
