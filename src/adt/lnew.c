#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *
c_adt_lnew(void *v, usize n)
{
	ctype_node *p;

	if (!(p = c_std_alloc(1, sizeof(*p)))) return nil;
	p->next = p;
	p->prev = nil;

	if (n) {
		if (!(p->p = c_std_alloc(n, sizeof(uchar)))) {
			c_std_free(p);
			return nil;
		}
		c_mem_cpy(p->p, v, n);
	} else {
		p->p = v;
	}
	return p;
}
