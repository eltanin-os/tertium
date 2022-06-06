#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_arr_tofrom(ctype_arr *dest, ctype_arr *s)
{
	return c_arr_cat(dest, c_arr_data(s), c_arr_bytes(s), sizeof(uchar));
}
