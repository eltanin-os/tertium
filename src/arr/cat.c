#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_arr_cat(Membuf *p, void *v, usize n)
{
	if (n > c_arr_avail(p))
		return -1;

	c_mem_cpy(p->p + p->n, n, v);
	p->n += n;
	p->p[p->n] = '\0';

	return 0;
}

