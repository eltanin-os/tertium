#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_exc_varglist(char *prog, va_list ap)
{
	usize len;
	int i, n;
	char *s;
	char **av;
	va_list tmp;

	va_copy(tmp, ap);
	for (n = 1; va_arg(tmp, char *); ++n) ;
	va_end(tmp);

	len = 1;
	for (s = prog; *s; ++s) {
		if (*s == ' ') ++n;
		++len;
	}

	s = c_std_alloc(len + ((n + 1) * sizeof(void *)) + 1, sizeof(uchar));
	if (!s) return nil;
	c_mem_cpy(s, len, prog);
	av = (void *)(s + len);

	i = 1;
	av[0] = s;
	for (; *s; ++s) {
		if (*s == ' ') {
			*s++ = 0;
			av[i++] = s;
		}
	}
	for (; i <= n; ++i) av[i] = va_arg(ap, char *);
	return av;
}
