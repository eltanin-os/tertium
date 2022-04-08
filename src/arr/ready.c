#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_ready(ctype_arr *p, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}
	if ((m *= n) > c_arr_avail(p)) {
		errno = C_ENOMEM;
		return -1;
	}
	return 0;
}
