#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_lswap(ctype_node **sp)
{
	ctype_node *a, *b, *c;

	a = *sp;
	if (!(b = a->prev)) return -1;
	c = b->prev;

	b->prev = a;
	b->next = a->next;
	a->next = b;
	a->prev = c;

	if (c) c->next = a;
	*sp = b;
	return 0;
}
