#include <tertium/cpu.h>
#include <tertium/std.h>

CNode *
c_adt_lnew(void *v, usize m, usize n)
{
	CArr   arr;
	CNode *np;

	c_mem_set(&arr, sizeof(arr), 0);
	if (c_dyn_cat(&arr, v, m, n) < 0)
		return nil;

	if (!(np = c_std_alloc(1, sizeof(*np))))
		return nil;

	np->p = c_arr_data(&arr);

	return np;
}
