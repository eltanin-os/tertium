#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_nput(CIoq *p, char *s, usize n)
{
	size r;

	if (n > c_arr_avail(p->mb))
		c_ioq_flush(p);

	while (n > c_arr_avail(p->mb)) {
		if ((r = (p->op)(p->fd, s, C_BIOSIZ)) < 0)
			return r;
		n -= r;
		s += r;
	}

	c_mem_cpy(p->mb->p + p->mb->n, n, s);
	p->mb->n += n;

	return n;
}
