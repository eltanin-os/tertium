#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_lpush(ctype_node **sp, ctype_node *p)
{
	if (!p)
		return -1;

	if ((p->prev = *sp)) {
		p->next = (*sp)->next;
		(*sp)->next = p;
	} else {
		p->next = p;
	}
	*sp = p;
	return 0;
}
