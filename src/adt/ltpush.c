#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_adt_ltpush(ctype_node **sp, ctype_node *p)
{
	if (!p)
		return -1;

	p->prev = nil;
	if (*sp) {
		if (!(p->next = (*sp)->next)->prev)
			p->next->prev = p;
		(*sp)->next = p;
	} else {
		*sp = p;
		p->next = p;
	}
	return 0;
}
