#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_gen_dirname(char *s)
{
	usize n;

	if (!s || !*s)
		return ".";

	n = c_str_len(s);
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
