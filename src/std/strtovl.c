#include <tertium/cpu.h>
#include <tertium/std.h>

vlong
c_std_strtovl(char *p, int b, vlong l, vlong h, char **e, int *r)
{
	vlong x;

	if ((x = c_std_strtouvl(p, b, 0, h, e, r)) < l) {
		if (r)
			*r = -1;
		errno = C_ERANGE;
	}
	return x;
}
