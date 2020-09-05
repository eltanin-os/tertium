#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static int
cmp(void *a, void *b)
{
	return (*(char *)a - ((struct fmtverb *)b)->c);
}

ctype_status
c_fmt_install(int c, ctype_fmtfn f)
{
	struct fmtverb *l, *p;
	struct fmtverb nf;
	usize n;

	nf = (struct fmtverb){ c, f };
	if (!(n = c_arr_bytes(&__fmt_Fmts)))
		return c_dyn_cat(&__fmt_Fmts, &nf, 1, sizeof(nf));
	if ((l = c_arr_data(&__fmt_Fmts))->c > c)
		return c_dyn_icat(&__fmt_Fmts, &nf, 1, sizeof(nf), 0);
	n /= sizeof(*p);
	p = c_std_nbsearch(&c, l, n, sizeof(*l), &cmp);
	if (p->c == c) {
		p->f = f;
		return 0;
	}
	return c_dyn_icat(&__fmt_Fmts, &nf, 1, sizeof(nf), (p + 1) - l);
}
