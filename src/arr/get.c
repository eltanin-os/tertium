#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_arr_get(CArr *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return nil;
	}

	m *= n;

	if (m > c_arr_avail(p)) {
		errno = C_ENOMEM;
		return nil;
	}

	return (p->p+m);
}
