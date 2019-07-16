#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

int
c_dir_open(CDir *p, char **argv, uint opts, int (*f)(void *, void *))
{
	CNode *np;
	CDent *ep;

	c_mem_set(p, sizeof(*p), 0);
	np = nil;

	for (; *argv; argv++) {
		if (c_adt_lpush(&np, __dir_newfile("", *argv, opts)) < 0) {
			while (np)
				c_adt_lfree(c_adt_lpop(&np));

			return -1;
		}

		ep = np->p;
		ep->info = __dir_info(p, ep);

		if (ep->info == C_FSDOT)
			ep->info = C_FSD;
	}

	if (f)
		c_adt_lsort(&np, f);

	p->f = f;
	p->cur = np->next;
	p->opts = opts;

	return 0;
}
