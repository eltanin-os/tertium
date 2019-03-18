#include <tertium/cpu.h>
#include <tertium/std.h>

CNode *
c_dst_lpop(CNode **sp)
{
	CNode *o;

	if (!*sp)
		return nil;

	o = *sp;

	if ((*sp = o->prev))
		(*sp)->next = o->next;

	return o;
}
