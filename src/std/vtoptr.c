#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_std_vtoptr_(char *s, ...)
{
	ctype_arr arr;
	int i, n;
	char **av;
	va_list ap;

	va_start(ap, s);
	for (n = 1; va_arg(ap, char *); ++n) ;
	va_end(ap);

	c_mem_set(&arr, sizeof(arr), 0);
	if (c_dyn_ready(&arr, n + 1, sizeof(char *)) < 0) return nil;
	av = c_arr_data(&arr);

	av[0] = s;
	va_start(ap, s);
	for (i = 1; i <= n; ++i) av[i] = va_arg(ap, char *);
	va_end(ap);
	return av;
}
