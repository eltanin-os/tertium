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
		ep = p->cur->p;
		switch (ep->info) {
		case C_FSD:
			p->child = p->ccur = __dir_builddir(p);
			break;
		case C_FSINT:
			p->ccur = p->cur;
			break;
		default:
			return nil;
		}
		return p->ccur->p;
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
