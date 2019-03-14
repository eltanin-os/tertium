#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_str_len(char *s)
{
	return (char *)c_mem_chr(s, C_USIZEMAX, 0)-s;
}
