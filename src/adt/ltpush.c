#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_ltpush(ctype_node **sp, ctype_node *p)
{
	if (!p)
		return -1;

	if (*sp) {
		p->next = (*sp)->next;
		(*sp)->next = ((*sp)->next)->prev = p;
	} else {
		*sp = p;
		p->next = p;
	}

	return 0;
}
