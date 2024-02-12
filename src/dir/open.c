#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

ctype_status
c_dir_open(ctype_dir *p, char **argv, uint opts, ctype_cmpfn f)
{
	ctype_dent *ep;
	ctype_node *np, *dummy;
	ctype_stat st;

	if (!(dummy = _tertium_dir_newfile("", ".", C_DIR_FSNOI))) return -1;
	ep = dummy->p;
	ep->info = C_DIR_FSINT;

	np = nil;
	if (c_nix_stat(&st, ".") < 0) goto err;

	c_mem_set(p, sizeof(*p), 0);
	p->dev = st.dev;
	p->opts = opts;
	for (; *argv; ++argv) {
		if (c_adt_lpush(&np,
		    _tertium_dir_newfile("", *argv, opts)) < 0) {
			goto err;
		}
		ep = np->p;
		ep->info = _tertium_dir_info(p, ep);
		ep->parent = dummy->p;
		if (p->opts & C_DIR_FSSTP) goto err;
	}
	if (f) c_adt_lsort(&np, f);
	if (c_adt_ltpush(&np, dummy) < 0) goto err;
	p->f = f;
	p->cur = np->next;
	return 0;
err:
	if (dummy) c_adt_lfree(dummy);
	while (np) c_adt_lfree(c_adt_lpop(&np));
	return -1;
}
