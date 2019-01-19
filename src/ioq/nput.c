#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_nput(Ioq *p, char *s, usize n)
{
	if (n > c_arr_avail(p->mb))
		c_ioq_flush(p);

	while (n > c_arr_avail(p->mb))
		if (!(n -= (p->op)(p->fd, s, MIN(n, IOQBUFSIZ))))
			return 0;

	c_mem_cpy(p->mb->p + p->mb->n, n, s);
	p->mb->n += n;

	return n;
}
