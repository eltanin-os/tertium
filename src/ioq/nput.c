#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_nput(ctype_ioq *p, char *s, usize n)
{
	size r, v;

	v = n;

	if (n > c_arr_avail(p->mb)) {
		if (p->opts & __IOQ_ONOFLUSH) {
			if (c_dyn_ready(p->mb, n, sizeof(uchar)) < 0)
				return -1;
		} else {
			if (c_ioq_flush(p) < 0)
				return -1;
			while (n > c_arr_avail(p->mb)) {
				r = C_MIN(n, C_BIOSIZ);
				if (c_sys_allrw(p->op, p->fd, s, r) < 0)
					return r;
				n -= r;
				s += r;
			}
		}
	}

	c_mem_cpy(p->mb->p + p->mb->n, n, s);
	p->mb->n += n;

	return v;
}
