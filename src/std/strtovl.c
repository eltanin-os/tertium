#include <tertium/cpu.h>
#include <tertium/std.h>

vlong
c_std_strtovl(char *p, int b, vlong l, vlong h, char **e, int *r)
{
	return c_std_strtouvl(p, b, l, h, e, r);
}
