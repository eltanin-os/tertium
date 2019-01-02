#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_ioq_nput(Ioq *p, char *s, usize n)
{
	if (n > c_arr_avail(p->mb))
		c_ioq_flush(p);
	c_mem_cpy(p->mb->p + p->mb->n, s, n);
	p->mb->n += n;
	return 0;
}
