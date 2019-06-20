#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_rchr(char *v, usize n, int c)
{
	return c_mem_rchr(v, c_str_len(v, n) + 1, c);
}
