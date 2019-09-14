#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_dent *
c_dir_children(ctype_dir *p)
{
	ctype_dent *ep;
	ctype_node *cur;

	cur = p->ccur;

	if (!cur) {
		cur = p->child ? p->child : p->cur;
		ep = cur->p;
		p->ccur = cur;
		return ep;
	}

	cur = cur->next;
	if (cur->prev) {
		p->ccur = cur;
		ep = cur->p;
		return ep;
	}

	p->ccur = nil;
	return nil;
}
