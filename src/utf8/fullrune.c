#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_utf8_fullrune(char *s, usize n)
{
	ctype_rune r;
	return c_utf8_charntorune(&r, s, n) > 0;
}
