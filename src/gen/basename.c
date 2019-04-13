#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_gen_basename(char *s)
{
	usize n;
	char *p;

	if (!s || !*s)
		return ".";

	n = c_str_len(s, C_USIZEMAX);
	n--;

	for (; s[n] == '/'; n--)
		;

	s[n+1] = 0;

	if (!(p = c_mem_rchr(s, n, '/')))
		return s;

	return ++p;
}
