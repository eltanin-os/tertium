#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_hsh_str(char *buf, ctype_hmd *p, char *data, usize n)
{
	ctype_hst h;
	p->init(&h);
	p->update(&h, data, n);
	p->end(&h, buf);
}
