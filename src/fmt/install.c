#include <tertium/cpu.h>
#include <tertium/std.h>

#include "verb.h"

int
c_fmt_install(int c, int (*f)(CFmt *))
{
	struct fmtverb *p;
	struct fmtverb  nf;
	int i;

	i = 0;

	for (; i < c_arr_len(&Fmts, sizeof(*p)); i++) {
		p = c_arr_get(&Fmts, i, sizeof(*p));
		if (p->c == c) {
			p->f = f;
			return 0;
		}
	}

	nf.c = c;
	nf.f = f;

	if (c_arr_cat(&Fmts, &nf, sizeof(nf)) < 0)
		return -1;

	return 0;
}
