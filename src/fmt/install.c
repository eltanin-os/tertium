#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_status
c_fmt_install(int c, ctype_fmtfn f)
{
	struct fmtverb *p;
	struct fmtverb nf;
	int i, n;

	n = c_arr_len(&__fmt_Fmts, sizeof(*p));
	for (i = 0; i < n; ++i) {
		p = c_arr_get(&__fmt_Fmts, i, sizeof(*p));
		if (p->c == c) {
			p->f = f;
			return 0;
		}
	}
	nf.c = c;
	nf.f = f;
	return c_arr_cat(&__fmt_Fmts, &nf, 1, sizeof(nf)) < 0 ? -1 : 0;
}
