#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_hsh_initk(ctype_hst *p, void *k, usize n)
{
	c_mem_cpy(p->buf, n, k);
}
