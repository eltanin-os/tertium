#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_dyn_tofrom(ctype_arr *dest, ctype_arr *s)
{
	return c_dyn_cat(dest, c_arr_data(s), c_arr_bytes(s), sizeof(uchar));
}
