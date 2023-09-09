#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_cpy(char *dest, usize n, char *src)
{
	return c_mem_cpy(dest, src, c_str_len(src, n));
}
