#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

ctype_dent *
c_dir_children(ctype_dir *p)
{
	ctype_dent *ep;
	ctype_node *cur;

	if (!(cur = p->ccur)) {
		ep = p->cur->p;
		if (ep->info != C_DIR_FSD) return nil;
		p->child = p->ccur = _tertium_dir_builddir(p);
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
