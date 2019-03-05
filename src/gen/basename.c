#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_gen_basename(char *s)
{
	usize n;
	char *p;

	if (!s || !*s)
		return ".";

	n = (char *)c_mem_chr(s, C_USIZEMAX, 0)-s;
	n--;

	for (; s[n] == '/'; n--)
		;

	s[n+1] = 0;

	if (!(p = c_mem_rchr(s, n, '/')))
		return s;

	return ++p;
}
