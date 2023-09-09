#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_dup(char *s, usize n)
{
	char *p;

	n = c_str_len(s, n);
	if (!(p = c_std_alloc(n+1, sizeof(uchar))))
		return nil;

	c_mem_cpy(p, s, n);
	p[n] = 0;
	return p;
}
