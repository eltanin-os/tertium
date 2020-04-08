#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_ready(ctype_arr *p, usize m, usize n)
{
	usize a;
	void *tmp;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	m *= n;
	m += n;
	a = p->a ? p->a : m;
	while (m > c_arr_avail(p)) {
		a <<= 1;
		if (!(tmp = c_std_realloc(p->p, a, sizeof(uchar))))
			return -1;
		p->p = tmp;
		p->a = a;
	}
	return 0;
}
