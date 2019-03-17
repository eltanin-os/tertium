#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpop(CQueue *p, CArr *b, usize m, usize n)
{
	if (C_OFLW_UM(usize, m, n))
		return -1;

	m *= n;

	if (!c_arr_bytes(p->mb))
		return 0;

	m = (m > c_arr_bytes(p->mb)) ? c_arr_bytes(p->mb) : m;

	if (c_arr_cat(b, c_arr_bget(p->mb, p->os), m, sizeof(uchar)) < 0)
		return -1;

	p->mb->n -= m;
	p->os += m+1;

	return 0;
}
