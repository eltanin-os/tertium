#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

void
__hsh_update(void (*f)(ctype_hst *, char *), int b,
    ctype_hst *p, char *data, usize n)
{
	uint r;

	r = p->len % b;
	p->len += n;
	if (r) {
		if (n < b - r) {
			c_mem_cpy(p->buf + r, n, data);
			return;
		}
		c_mem_cpy(p->buf + r, b - r, data);
		n -= b - r;
		data += b - r;
		f(p, (char *)p->buf);
	}
	while (n >= (usize)b) {
		f(p, data);
		n -= b;
		data += b;
	}
	c_mem_cpy(p->buf, n, data);
}
