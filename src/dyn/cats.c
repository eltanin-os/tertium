#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_dyn_cats(CArr *p, char *s)
{
	size   r;
	uchar *dst, *src;

	dst  = p->p + p->n;
	r    = 0;
	src  = (uchar *)s;
	p->a = c_arr_avail(p) ? p->a : 64;

	for (;;) {
		while (++r > c_arr_avail(p)) {
			p->a *= 2;
			if (!(p->p = c_std_realloc(p->p, p->a, sizeof(uchar))))
				return -1;
		}
		if (!(*dst++ = *src++))
			break;
	}

	p->n += r;
	p->p[p->n] = 0;

	return r;
}
