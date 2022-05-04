#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_ready(ctype_arr *p, usize m, usize n)
{
	if (C_STD_OVERFLOWM(usize, m, n)) {
		errno = C_ERR_EOVERFLOW;
		return -1;
	}
	if ((m *= n) > c_arr_avail(p)) {
		errno = C_ERR_ENOMEM;
		return -1;
	}
	return 0;
}
