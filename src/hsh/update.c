#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

typedef void (*hfunc)(ctype_hst *, char *);

void
c_hsh_update(hfunc f, int b, ctype_hst *p, char *data, usize n)
{
	usize len;

	while (n) {
		if (!p->curlen && n >= (uint)b) {
			f(p, data);
			p->len += b << 3;
			data += b;
			n -= b;
		} else {
			len = C_MIN(n, b - p->curlen);
			c_mem_cpy(p->buf + p->curlen, len, data);
			p->curlen += len;
			data += len;
			n -= len;
			if (p->curlen == (uint)b) {
				f(p, data);
				p->len += b << 3;
				p->curlen = 0;
			}
		}
	}
}
