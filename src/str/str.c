#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_str(char *h, usize n, char *s)
{
	return c_mem_mem(h, c_str_len(h, n), s, c_str_len(s, C_USIZEMAX));
}
