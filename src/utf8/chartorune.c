#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_utf8_chartorune(ctype_rune *p, char *s)
{
	return c_utf8_charntorune(p, s, C_UTF8_MAX);
}
