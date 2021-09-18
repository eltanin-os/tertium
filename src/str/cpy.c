#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_cpy(char *dest, usize n, char *src)
{
	for (; n && (*dest = *src); --n, ++dest, ++src) ;
	return dest;
}
