#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpops(CArr *p, CArr *b)
{
	usize *o;
	usize  n;
	uchar *s;

	if (c_arr_bytes(p) == sizeof(o) * 2)
		return 0;

	o = (void *)(uintptr)(p->p + sizeof(o) * 0);
	s = c_arr_bget(p, *o);
	n = (uchar *)c_mem_chr(s, C_USIZEMAX, 0)-s;

	return c_dst_qpop(p, b, n, sizeof(uchar));
}
