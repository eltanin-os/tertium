#include <tertium/cpu.h>
#include <tertium/std.h>

static usize
movemem(ctype_arr *p, char *b, usize n)
{
	n = C_MIN(n, p->n);
	c_mem_cpy(b, n, p->p + p->a);
	p->n -= n;
	p->a += n;
	return n;
}

size
c_ioq_get(ctype_ioq *p, char *b, usize n)
{
	size r;

	if (p->arr.n)
		return movemem(&p->arr, b, n);

	if (n >= p->arr.a)
		return (p->op)(p->fd, b, n);

	if ((r = c_ioq_feed(p)) <= 0)
		return r;

	return movemem(&p->arr, b, n);
}
