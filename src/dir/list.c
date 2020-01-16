#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_dent *
c_dir_list(ctype_dir *p)
{
	ctype_dent *ep;
	ctype_node *cur;

	if (!(cur = p->ccur)) {
		p->ccur = p->cur;
		if ((ep = p->ccur->p)->info == C_FSINT) {
			p->ccur = p->ccur->next;
			ep = p->ccur->p;
		}
		return ep;
	}

	cur = cur->next;
	if (cur->prev) {
		p->ccur = cur;
		return cur->p;
	}

	p->ccur = nil;
	return nil;
}
