#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_gen_dirname(char *s)
{
	usize n;

	if (!s || !*s)
		return ".";

	n = (char *)c_mem_chr(s, C_USIZEMAX, 0)-s;
	n--;

	for (; s[n] == '/'; n--)
		if (!n)
			return "/";

	for (; s[n] != '/'; n--)
		if (!n)
			return ".";

	for (; s[n] == '/'; n--)
		if (!n)
			return "/";

	s[++n] = 0;

	return s;
}
