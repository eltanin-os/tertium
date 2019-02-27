#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_nput(CIoq *p, char *s, usize n)
{
	size r, v;

	v = n;

	if (n > c_arr_avail(p->mb))
		if (c_ioq_flush(p) < 0)
			return -1;

	while (n > c_arr_avail(p->mb)) {
		if ((r = c_sys_allrw(p->op, p->fd, s, C_MIN(n, C_BIOSIZ))) < 0)
			return r;
		n -= r;
		s += r;
	}

	c_mem_cpy(p->mb->p + p->mb->n, n, s);
	p->mb->n += n;

	return v;
}
