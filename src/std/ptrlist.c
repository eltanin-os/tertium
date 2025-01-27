#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_std_ptrlist_(char *s, ...)
{
	va_list ap;
	void *p;
	va_start(ap, s);
	p = c_std_vptrlist(s, ap);
	va_end(ap);
	return p;
}
