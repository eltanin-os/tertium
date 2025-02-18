#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_lrot(ctype_node **sp)
{
	ctype_node *a, *b, *c, *d;

	a = *sp;
	if (!(b = a->prev)) return 1;
	if (!(c = b->prev)) return 1;
	d = c->prev;

	c->next = a->next;
	a->next = c;
	b->prev = c->prev;
	c->prev = a;

	if (d) d->next = b;
	*sp = c;
	return 0;
}
