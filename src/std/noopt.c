#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_std_noopt(ctype_arg *p, char *s)
{
	if (s && s[0] == '-') {
		if (s[1] == '-' && s[2] == '\0') {
			++p->idx;
			return 0;
		} else if (s[1] == '\0') {
			return 0;
		} else {
			return (p->opt = s[1]);
		}
	}
	return 0;
}
