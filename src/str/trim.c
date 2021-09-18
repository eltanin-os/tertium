#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_str_trim(char *str, usize n, char *t)
{
	return c_str_ltrim(c_str_rtrim(str, n, t), n, t);
}
