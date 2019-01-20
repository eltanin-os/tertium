#include <tertium/cpu.h>
#include <tertium/std.h>

#include "verb.h"

int
c_fmt_install(int c, int (*f)(Fmt *))
{
	struct fmtverb *p;
	int i;

	i = 0;

	for (; i <= c_arr_len(&Fmts, sizeof(*p)); i++) {
		p = c_arr_get(&Fmts, i, sizeof(*p));
		if (p->c == c) {
			p->f = f;
			return 0;
		}
	}

	if (c_arr_cat(&Fmts, "\0", sizeof("\0")) < 0)
		return -1;

	p = c_arr_get(&Fmts, i, sizeof(*p));
	p->c = c;
	p->f = f;

	return 0;
}
