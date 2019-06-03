#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_hsh_digest(CHst *hs, CHmd *p, char *s)
{
	if (p->digest)
		p->digest(hs, s);

	return 0;
}
