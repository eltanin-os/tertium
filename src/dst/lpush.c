#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_lpush(CNode **sp, CNode *p)
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
