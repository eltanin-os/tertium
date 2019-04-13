#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_str(char *h, usize n, char *needle)
{
	usize hl;
	hl = c_str_len(h, C_USIZEMAX);
	n  = C_MIN(n, hl);
	return c_mem_mem(h, n, needle, c_str_len(needle, C_USIZEMAX));
}
