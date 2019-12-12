#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_nput(ctype_ioq *p, char *s, usize n)
{
	size r;

	if (n > c_arr_avail(&p->arr)) {
		if (p->opts & C_IOQ_ONOFLUSH) {
			if (!(p->opts & C_IOQ_ODYNAMIC)) {
				errno = C_ENOMEM;
				return -1;
			}
			if (c_dyn_ready(&p->arr, n, sizeof(uchar)) < 0)
				return -1;
		} else {
			if (c_ioq_flush(p) < 0)
				return -1;
			while (n > c_arr_avail(&p->arr)) {
				r = C_MIN(n, C_BIOSIZ);
				if (c_std_allrw(p->op, p->fd, s, r) < 0)
					return -1;
				n -= r;
				s += r;
			}
		}
	}

	c_mem_cpy(p->arr.p + p->arr.n, n, s);
	p->arr.n += n;
	return 0;
}
