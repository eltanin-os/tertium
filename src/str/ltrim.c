#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_ltrim(char *str, usize n, char *t)
{
	usize i, len, tlen;

	len = c_str_len(str, n);
	tlen = c_str_len(t, -1);
	for (i = 0; i < len; ++i) {
		if (!c_mem_chr(t, tlen, str[i]))
			break;
		str[i] = 0;
	}
	return str;
}
