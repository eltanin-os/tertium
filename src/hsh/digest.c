#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_hsh_digest(CHst *hs, CHmd *p, char *s)
{
	if (p->digest)
		p->digest(hs, s);
}
