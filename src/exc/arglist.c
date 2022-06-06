#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_exc_arglist_(char *prog, ...)
{
	char **av;
	va_list ap;
	va_start(ap, prog);
	av = c_exc_varglist(prog, ap);
	va_end(ap);
	return av;
}
