#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_arr_cats(CArr *p, char *s)
{
	size   r;
	uchar *dst, *src;

	dst = p->p + p->n;
	r   = 0;
	src = (uchar *)s;

	for (;;) {
		if (++r > c_arr_avail(p))
			return -1;
		if (!(*src++ = *dst++))
			break;
	}

	p->n += r;
	p->p[p->n] = 0;

	return r;
}
