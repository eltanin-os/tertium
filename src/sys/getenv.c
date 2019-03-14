#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_sys_getenv(char *s)
{
	usize n;
	int   i;

	if (!s || !environ)
		return nil;

	n = c_str_len(s);

	for (i = 0; environ[i]; i++)
		if (!(c_mem_cmp(environ[i], n, s)) && (environ[i][n] == '='))
			return environ[i]+n+1;

	return nil;
}
