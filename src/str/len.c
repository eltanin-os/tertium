#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_str_len(char *s, usize n)
{
	char *p;

	if (!(p = c_mem_chr(s, n, 0)))
		return n;

	return p - s;
}
