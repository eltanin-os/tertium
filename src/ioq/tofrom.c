#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_tofrom(ctype_ioq *dest, ctype_ioq *src, usize n)
{
	usize len, min;
	size r;

	len = n;
	while (len) {
		if ((r = c_ioq_feed(src)) < 0)
			return -1;
		if (!r)
			break;

		min = C_STD_MIN((usize)r, len);
		if (c_ioq_nput(dest, (char *)src->arr.p + src->arr.a, min) < 0)
			return -1;
		src->arr.n -= min;
		src->arr.a += min;
		len -= min;
	}
	return len ? n - len : n;
}
