#include <tertium/cpu.h>
#include <tertium/std.h>

#define PTRSIZ(a) ((a) * sizeof(char *))

void *
c_exc_arglist_(char *prog, ...)
{
	ctype_arr arr;
	usize len;
	int i, n;
	char *s;
	char **av;
	va_list ap;

	va_start(ap, prog);
	for (n = 1; va_arg(ap, char *); ++n) ;
	va_end(ap);

	len = 1;
	for (s = prog; *s; ++s) {
		if (*s == ' ')
			++n;
		++len;
	}

	c_mem_set(&arr, sizeof(arr), 0);
	if (c_dyn_ready(&arr, len + PTRSIZ(n + 1), sizeof(uchar)) < 0)
		return nil;

	av = c_arr_get(&arr, len, sizeof(uchar));
	av[0] = c_mem_cpy(c_arr_data(&arr), len, prog);
	i = 1;
	for (s = av[0]; *s; ++s) {
		if (*s == ' ') {
			*s++ = 0;
			av[i++] = s;
		}
	}

	va_start(ap, prog);
	for (; i <= n; ++i)
		av[i] = va_arg(ap, char *);
	va_end(ap);
	return av;
}
