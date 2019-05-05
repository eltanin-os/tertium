#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpops(CQueue *p, CArr *b)
{
	usize len, n;

	n   = c_arr_total(&p->mb) - p->h;
	len = c_str_len(c_arr_get(&p->mb, p->h, sizeof(uchar)), n);
	if (len == n)
		len += c_str_len(c_arr_data(&p->mb), p->mb.a);

	return c_dst_qpop(p, b, len, sizeof(uchar));
}
