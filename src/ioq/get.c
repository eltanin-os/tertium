#include <tertium/cpu.h>
#include <tertium/std.h>

static usize
extract(Ioq *p, char *b, usize n)
{
	if (n > p->mb->n)
		n = p->mb->n;

	c_mem_cpy(b, p->mb->p + p->mb->a, n);
	p->mb->n -= n;
	p->mb->a += n;

	return n;
}

size
c_ioq_get(Ioq *p, char *b, usize n)
{
	size r;

	if (p->mb->n)
		return extract(p, b, n);

	if (n >= p->mb->a)
		return (p->op)(p->fd, b, n);

	if ((r = c_ioq_feed(p)) <= 0)
		return r;

	return extract(p, b, n);
}
