#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_std_vptrlist(char *s, va_list ap)
{
	va_list tmp;
	usize i, n;
	char **av;

	va_copy(tmp, ap);
	for (n = 1; va_arg(tmp, char *); ++n) ;
	va_end(tmp);

	if (!(av = c_std_alloc(n + 1, sizeof(char *)))) return nil;
	av[0] = s;
	for (i = 1; i <= n; ++i) av[i] = va_arg(ap, char *);
	return av;
}
