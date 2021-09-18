#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_rtrim(char *str, usize n, char *t)
{
	usize len, tlen;

	len = c_str_len(str, n);
	tlen = c_str_len(t, -1);
	for (; len; --len) {
		if (!c_mem_chr(t, tlen, str[len]))
			break;
		str[len--] = 0;
	}
	return str;
}
