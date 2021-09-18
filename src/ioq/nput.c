#include <tertium/cpu.h>
#include <tertium/std.h>

#define BLK(x) C_MIN(C_BIOSIZ, (x))

ctype_status
c_ioq_nput(ctype_ioq *p, char *s, usize n)
{
	size r;

	if (n > c_arr_avail(&p->arr)) {
		if (c_ioq_flush(p) < 0)
			return -1;
		while (n > c_arr_avail(&p->arr)) {
			if ((r = c_nix_allrw(p->op, p->fd, s, BLK(n))) < 0)
				return -1;
			n -= r;
			s += r;
		}
	}
	c_mem_cpy(p->arr.p + p->arr.n, n, s);
	p->arr.n += n;
	return 0;
}
