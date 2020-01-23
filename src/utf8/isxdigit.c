#include <tertium/cpu.h>
#include <tertium/std.h>

/* <A-F>, <a-f>, Nd */
int
c_utf8_isxdigit(ctype_rune r)
{
	return c_utf8_isdigit(r) || ((r | 32) - 'a' < 6);
}
