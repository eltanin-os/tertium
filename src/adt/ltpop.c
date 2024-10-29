#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_node *
c_adt_ltpop(ctype_node **sp)
{
	ctype_node *n;

	if (!*sp) return nil;
	n = (*sp)->next;
	(*sp)->next = n->next;

	n->next->prev = nil;
	n->prev = nil;
	n->next = n;
	return n;
}
