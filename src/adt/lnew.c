#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *
c_adt_lnew(void *v, usize n)
{
	ctype_node *p;

	if (!(p = c_std_alloc(n + sizeof(*p), sizeof(uchar))))
		return nil;
	p->next = p;
	p->prev = nil;
	p->p = (void *)((uchar *)p + sizeof(*p));
	c_mem_cpy(p->p, n, v);
	return p;
}
