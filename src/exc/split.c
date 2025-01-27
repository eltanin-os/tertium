#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_exc_split_(char *prog, ...)
{
	va_list ap;
	void *p;
	va_start(ap, prog);
	p = c_exc_vsplit(prog, ap);
	va_end(ap);
	return p;
}
