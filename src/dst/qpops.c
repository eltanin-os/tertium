#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpops(CQueue *p, CArr *b)
{
	usize len, max;

	max = p->mb.a - p->h;

	if ((len = c_str_len(c_arr_bget(&p->mb, p->h), max)) == max)
		len += c_str_len(c_arr_bget(&p->mb, 0), p->mb.a);

	return c_dst_qpop(p, b, len, sizeof(uchar));
}
