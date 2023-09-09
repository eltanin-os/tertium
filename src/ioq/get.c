#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_get(ctype_ioq *p, char *b, usize n)
{
	usize len, min;
	size r;

	len = n;
	while (len) {
		if ((r = c_ioq_feed(p)) < 0)
			return -1;
		if (!r)
			break;

		min = C_STD_MIN((usize)r, len);
		c_mem_cpy(b, p->arr.p + p->arr.a, min);
		p->arr.n -= min;
		p->arr.a += min;
		len -= min;
		b += min;
	}
	return len ? n - len : n;
}
