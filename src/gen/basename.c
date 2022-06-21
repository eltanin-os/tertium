#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_gen_basename(char *s)
{
	usize n;
	char *p;

	if (!s) return nil;
	if (!*s) c_mem_cpy(s, sizeof("."), ".");

	n = c_str_len(s, -1);
	if (!--n) return s;

	for (; s[n] == '/'; --n) ;
	s[n + 1] = 0;

	if (!(p = c_mem_rchr(s, n, '/'))) return s;
	return ++p;
}
