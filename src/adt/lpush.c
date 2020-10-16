#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_lpush(ctype_node **sp, ctype_node *p)
{
	ctype_node *head;

	if (!p)
		return -1;

	head = p->next;
	if ((head->prev = *sp)) {
		p->next = (*sp)->next;
		(*sp)->next = head;
	}
	*sp = p;
	return 0;
}
