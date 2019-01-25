#include <tertium/cpu.h>
#include <tertium/std.h>

u32int
c_hsh_all(CH32md *p, char *data, usize n)
{
	CH32st hs;
	p->init(&hs);
	p->update(&hs, data, n);
	p->end(&hs);
	return hs.a;
}
