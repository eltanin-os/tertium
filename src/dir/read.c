#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_dent *
c_dir_read(ctype_dir *p)
{
	ctype_dent *ep;
	ctype_node *cur;
	int instr;

	cur = p->cur;
	ep = cur->p;

	if (!cur || (p->opts & C_FSSTP))
		return nil;

	instr = ep->instr;
	ep->instr = 0;

	if (instr == C_FSAGN) {
		ep->info = __dir_info(p, ep);
		return ep;
	}

	if (ep->info == C_FSDP)
		while (p->child)
			c_adt_lfree(c_adt_lpop(&p->child));

	if (ep->info == C_FSD) {
		if (instr == C_FSSKP ||
		    ((p->opts & C_FSXDV) && p->dev != ep->dev)) {
			ep->info = C_FSDP;
			return ep;
		}
		if (p->child) {
			;
		} else if ((p->child = __dir_builddir(p)) == (void *)-1) {
			ep->err = errno;
			ep->info = C_FSDNR;
			if (errno == C_ENOMEM) {
				p->opts |= C_FSSTP;
				ep->info = C_FSERR;
			}
			p->child = nil;
			return ep;
		}
		if (!p->child) {
			ep->info = C_FSDP;
			return ep;
		}
		cur = p->child;
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
		p->cur = cur;
		ep = cur->p;
		ep->info = C_FSDP;
		return ep;
	}

	while (p->cur)
		c_adt_lfree(c_adt_lpop(&p->cur));

	return nil;
}
