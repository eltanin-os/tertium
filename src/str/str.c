#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_str(char *h, char *n)
{
	return c_mem_mem(h, c_str_len(h), n, c_str_len(n));
}
