#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_ltpush(ctype_node **sp, ctype_node *p)
{
	ctype_node *head;

	if (!p)
		return -1;

	if (*sp) {
		head = p->next;
		p->next = (*sp)->next;
		p->next->prev = p;
		(*sp)->next = head;
	} else {
		*sp = p;
	}
	return 0;
}
