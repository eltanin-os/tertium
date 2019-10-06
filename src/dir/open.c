#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_status
c_dir_open(ctype_dir *p, char **argv, uint opts, ctype_cmpfn f)
{
	ctype_dent *ep;
	ctype_node *np, *dummy;
	ctype_stat st;

	c_mem_set(p, sizeof(*p), 0);

	if (!(dummy = __dir_newfile("", ".", C_FSNOI)))
		return -1;

	np = nil;

	if (c_sys_stat(&st, ".") < 0)
		goto err;

	p->dev = st.dev;
	p->opts = opts;

	for (; *argv; argv++) {
		if (c_adt_lpush(&np, __dir_newfile("", *argv, opts)) < 0)
			goto err;

		ep = np->p;
		ep->info = __dir_info(p, ep);
		ep->parent = dummy->p;

		if (ep->info == C_FSDOT)
			ep->info = C_FSD;

		if (p->opts & C_FSSTP)
			goto err;
	}

	if (f)
		c_adt_lsort(&np, f);

	if (c_adt_ltpush(&np, dummy) < 0)
		goto err;

	p->f = f;
	p->cur = np->next;

	return 0;
err:
	if (dummy)
		c_adt_lfree(dummy);
	while (np)
		c_adt_lfree(c_adt_lpop(&np));

	return -1;
}
