#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_sys_getenv(char *s)
{
	usize n;
	char **p;

	if (!s || !environ)
		return nil;

	n = (char *)c_mem_chr(s, USIZE_MAX, 0)-s;

	p = environ;
	for (; *p; p++)
		if (!(c_mem_cmp(*p, n, s)) && (*p[n] == '='))
			return *p+n+1;

	return nil;
}
