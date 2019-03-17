#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpush(CQueue *p, void *v, usize m, usize n)
{
	usize  ws;

	if (C_OFLW_UM(usize, m, n))
		return -1;

	m *= n;

	if (m > c_arr_avail(p->mb))
		return -1;

	if (p->oe + m > p->mb->a) {
		ws = p->mb->a - p->oe;
		if (m + ws > c_arr_avail(p->mb))
			return -1;
		p->mb->n += ws;
		p->oe = 0;
	}

	c_mem_cpy(c_arr_bget(p->mb, p->oe), m, v);
	p->mb->n += m;
	p->oe += m+1;
	p->mb->p[p->oe-1] = 0;

	return 0;
}
