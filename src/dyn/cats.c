#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_dyn_cats(CArr *p, char *s)
{
	size   r;
	uchar *dst, *src;

	r   = 0;
	src = (uchar *)s;

	if (!p->a && !c_dyn_alloc(p, 64, sizeof(uchar)))
		return -1;

	dst = p->p + p->n;

	for (;;) {
		while (++r > c_arr_avail(p))
			if (!c_dyn_alloc(p, p->a*2, sizeof(uchar)))
				return -1;
		if (!(*dst++ = *src++))
			break;
	}

	p->n += --r;
	p->p[p->n] = 0;

	return r;
}
