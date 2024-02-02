#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

static int
cmp(void *a, void *b)
{
	return *(uchar *)a - ((struct fmtverb *)b)->c;
}

ctype_status
c_fmt_install(ctype_rune c, ctype_fmtfn f)
{
	struct fmtverb *p;
	struct fmtverb nent;
	ctype_arr *ap;
	usize n;
	uchar *s;

	ap = &_tertium_fmt_fmts;
	if (c_dyn_ready(ap, 1, sizeof(nent)))
		return -1;

	n = c_arr_len(ap, sizeof(*p));
	s = c_arr_data(ap);
	p = c_std_nbsearch(&c, s, n, sizeof(*p), &cmp);
	if (p->c == c) {
		p->f = f;
		return 0;
	}
	nent = (struct fmtverb){ c, f };
	n = (((uchar *)p - s) / sizeof(*p)) + !!n;
	return c_dyn_idxcat(ap, n, &nent, 1, sizeof(nent));
}
