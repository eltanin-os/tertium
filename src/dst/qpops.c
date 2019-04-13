#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpops(CQueue *p, CArr *b)
{
	usize n;

	if (!c_arr_bytes(p->mb))
		return 0;

	n = c_str_len(c_arr_bget(p->mb, p->os), C_USIZEMAX);
	return c_dst_qpop(p, b, n, sizeof(uchar));
}
