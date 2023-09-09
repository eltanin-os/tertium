#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_hsh_initk(ctype_hst *p, void *k, usize n)
{
	if (n > sizeof(p->buf)) n = sizeof(p->buf); /* XXX */
	c_mem_cpy(p->buf, k, n);
	c_mem_set(p->buf + n, sizeof(p->buf) - n, 0);
}
