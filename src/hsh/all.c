#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_hsh_all(CHst *hs, CHmd *p, char *data, usize n)
{
	p->init(hs);
	p->update(hs, data, n);
	p->end(hs);
}
