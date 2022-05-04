#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

ctype_dent *
c_dir_read(ctype_dir *p)
{
	ctype_dent *ep;
	ctype_node *cur;
	int instr;

	cur = p->cur;
	ep = cur->p;
	if (!cur || (p->opts & C_DIR_FSSTP))
		return nil;

	instr = ep->instr;
	ep->instr = 0;
	if (instr == C_DIR_FSAGN) {
		ep->info = _tertium_dir_info(p, ep);
		return ep;
	}

	if (ep->info == C_DIR_FSD) {
		if (instr == C_DIR_FSSKP ||
		    ((p->opts & C_DIR_FSXDV) && p->dev != ep->dev)) {
			ep->info = C_DIR_FSDP;
			return ep;
		}
		if (p->child) {
			;
		} else if ((p->child = _tertium_dir_builddir(p)) == BFAIL) {
			ep->err = errno;
			ep->info = C_DIR_FSDNR;
			if (errno == C_ERR_ENOMEM) {
				p->opts |= C_DIR_FSSTP;
				ep->info = C_DIR_FSERR;
			}
			p->child = nil;
			return ep;
		} else if (!p->child) {
			ep->info = C_DIR_FSDP;
			return ep;
		}
		cur = p->child;
		p->child = nil;
		p->cur = cur;
		ep = cur->p;
		return ep;
	}

	cur = cur->next;
	if (cur->prev) {
		p->cur = cur;
		ep = cur->p;
		return ep;
	}

	cur = ep->__p;
	if (cur) {
		while (p->cur)
			c_adt_lfree(c_adt_lpop(&p->cur));

		p->cur = cur;
		ep = cur->p;
		ep->info = C_DIR_FSDP;
		return ep;
	}
	return nil;
}
